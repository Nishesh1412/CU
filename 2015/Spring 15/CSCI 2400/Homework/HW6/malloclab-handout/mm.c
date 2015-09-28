/*
* mm-implicit.c -  Simple allocator based on implicit free lists,
*                  first fit placement, and boundary tag coalescing.
*
* Each block has header and footer of the form:
*
*      31                     3  2  1  0
*      -----------------------------------
*     | s  s  s  s  ... s  s  s  0  0  a/f
*      -----------------------------------
*
* where s are the meaningful size bits and a/f is set
* iff the block is allocated. The list has the following form:
*
* begin                                                          end
* heap                                                           heap
*  -----------------------------------------------------------------
* |  pad   | hdr(8:a) | ftr(8:a) | zero or more usr blks | hdr(8:a) |
*  -----------------------------------------------------------------
*          |       prologue      |                       | epilogue |
*          |         block       |                       | block    |
*
* The allocated prologue and epilogue blocks are overhead that
* eliminate edge conditions during coalescing.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include "mm.h"
#include "memlib.h"

/*********************************************************
* NOTE TO STUDENTS: Before you do anything else, please
* provide your team information in the following struct.
********************************************************/
team_t team = {
  /* Team name */
  "My Team",
  /* First member's full name */
  "Nishesh Shukla",
  /* First member's email address */
  "nish3996@colorado.edu",
  /* Second member's full name (leave blank if none) */
  "",
  /* Second member's email address (leave blank if none) */
  ""
};

/////////////////////////////////////////////////////////////////////////////
// Constants and macros
//
// These correspond to the material in Figure 9.43 of the text
// The macros have been turned into C++ inline functions to
// make debugging code easier.
//

// source github mightydeveloper/malloc
// source computer systems old edition book
/////////////////////////////////////////////////////////////////////////////
#define WSIZE       4 // word size, bytes
#define DSIZE       8 // dobule wordsize, bytes
#define CHUNKSIZE  (1<<12)// initial heap size, bytes

#define MINSIZE   16

#define OVERHEAD    8 // Overhead of header and footer, bytes

#define LISTS       20 // number of lists
#define BUFFER  (1<<7)// reallocation buffer

#define PRED_PTR(bp) ((char *)(bp))// address of free block's predecessor value
#define SUCCESS_PTR(bp) ((char *)(bp) + WSIZE) //address of free block's successor value
#define PREDEC(bp) (*(char **)(bp)) //address of free block's predecessor on the segregated list
#define SUCCESS(bp) (*(char **)(SUCCESS_PTR(bp))) //address of free block's successor on the segregated list
#define SET_POINTER(p, bp) (*(unsigned int *)(p) = (unsigned int)(bp))//pointer for free blocks
#define TAG_SET(p)   (*(unsigned int *)(p) = GET(p) | 0x2)//reallocation tag
#define TAG_UNSET(p) (*(unsigned int *)(p) = GET(p) & ~0x2)//reallocation tag
#define ALIGN(p) (((size_t)(p) + 7) & ~(0x7))//checks for allignment
#define PUT_NOTAG(p, val) (*(unsigned int *)(p) = (val))
static inline int MAX(int x, int y) {
  return (x > y ? x : y);
}
static inline int MIN(int x, int y){
  return (x < y ? x : y);
}

//
// Pack a size and allocated bit into a word
// We mask of the "alloc" field to insure only
// the lower bit is used
//
static inline size_t PACK(size_t size, int alloc) {
  return ((size) | (alloc & 0x1));
}

//
// Read and write a word at address p
//
static inline size_t GET(void *p) {
  return  *(size_t *)p; 
}
static inline void PUT(void *p, size_t val){
  *((size_t *)p) = val;
}

//
// Read the size and allocated fields from address p
//
static inline size_t GET_SIZE(void *p)  {
  return GET(p) & ~0x7;
}

static inline int GET_ALLOC(void *p) {
  return GET(p) & 0x1;
}

static inline int GET_TAG(void *p){
  return GET(p) & 0x2;
}

//
// Given block ptr bp, compute address of its header and footer
//
static inline void *HDRP(void *bp) {
  return ((char *)bp) - WSIZE;
}
static inline void *FTRP(void *bp) {
  return ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE);
}

//
// Given block ptr bp, compute address of next and previous blocks
//
static inline void *NEXT_BLKP(void *bp) {
  return ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)));
}

static inline void* PREV_BLKP(void *bp){
  return ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)));
}


/////////////////////////////////////////////////////////////////////////////
//
// Global Variables
//

//Pointer -> first block
static char *heap_listp;
//Array of pointers -> free lists
void *working_lists[LISTS];

//
// function prototypes for internal helper routines
//
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
//static void *find_fit(size_t asize);
static void *coalesce(void *bp);
//static void printblock(void *bp);
//static void checkblock(void *bp);
static void insert_node(void *bp, size_t size);
static void delete_node(void *bp);

//
// mm_init - Initialize the memory manager 
//
int mm_init(void) // source computer systems book page 747 (old edition)
{
  int list;//list counter

  for (list = 0; list < LISTS; list++){ //initializes array of pointers in order to divide the free lists
    working_lists[list] = NULL;
  }
  //Creating an inital empty heap
  if ((long)(heap_listp = mem_sbrk(4 * WSIZE)) == -1){
    return -1;
  }
  PUT(heap_listp, 0);//alignment
  PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));//Prologue header
  PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));//Prologue footer
  PUT(heap_listp + (3 * WSIZE), PACK(0, 1));//Epilogue header
  heap_listp += (2 * WSIZE);

  if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
    return -1;
  return 0;
}


//
// extend_heap - Extend heap with free block and return its block pointer
//
static void *extend_heap(size_t words)// source computer systems book page 748 (old edition)
{
  void *bp;
  size_t size;
  size_t n_size = words / WSIZE;

  size = (n_size % 2) ? (n_size + 1) * WSIZE : n_size * WSIZE;
  if ((long)(bp = mem_sbrk(size)) == -1){
    return NULL;
  }

  //Initialize free block header/footer and the epilogue header
  PUT_NOTAG(HDRP(bp), PACK(size, 0)); //free block HDRP
  PUT_NOTAG(FTRP(bp), PACK(size, 0)); //free block FTRP
  PUT_NOTAG(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); //new epilogue header
  insert_node(bp, size);//inserts new block -> correct list.
  return coalesce(bp);
}

// 
// mm_free - Free a block 
//
void mm_free(void *bp) // source computer systems book page 749 (old edition)
{
  size_t size = GET_SIZE(HDRP(bp));

  TAG_UNSET(HDRP(NEXT_BLKP(bp)));
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  insert_node(bp, size);//inserts new block -> correct list.
  coalesce(bp);
}

//
// coalesce - boundary tag coalescing. Return ptr to coalesced block
//
static void *coalesce(void *bp) // source computer systems book page 749 (old edition)
{
  size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));
  //CASE 1
  if (prev_alloc && next_alloc)
  { 
    return bp;
  }
  else if (GET_TAG(HDRP(PREV_BLKP(bp))))//if previous block -> tagged, DO NOT coalesce.
    prev_alloc = 1;
  
  delete_node(bp);//delete old block from list.
  
  //CASE 2
  if (prev_alloc && !next_alloc) {
    delete_node(NEXT_BLKP(bp));
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }

  //CASE 3
  else if (!prev_alloc && next_alloc) {
    delete_node(PREV_BLKP(bp));
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }

  //CASE 4
  else
  { 
    delete_node(PREV_BLKP(bp));
    delete_node(NEXT_BLKP(bp));
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
      GET_SIZE(FTRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }
  insert_node(bp, size);// insert new block -> correct list
  return bp;
}

//
// mm_malloc - Allocate a block with at least size bytes of payload 
//
void *mm_malloc(size_t size) // source computer systems book page 750 (old edition)
{
  size_t asize; //Adjusted blocksize
  size_t extendsize; //amount to extend heap if it doesnt fit
  char *bp = NULL;
  int list = 0;

  if (size == 0){
    return NULL;
  }
  //Adjust block size to include => overhead & alignment requests.
  if (size <= DSIZE){
    asize = 2 * DSIZE;
  }

  else{
    asize = DSIZE * ((size + (DSIZE)+(DSIZE - 1)) / DSIZE);
  }

  size = asize;
  while (list < LISTS)
  {
    if ((list == LISTS - 1) || ((size <= 1) && (working_lists[list] != NULL))){
      bp = working_lists[list];
      while ((bp != NULL)//if the blocks are too small, they are not taken.
        && ((asize > GET_SIZE(HDRP(bp))) || (GET_TAG(HDRP(bp)))))
      {
        bp = PREDEC(bp);
      }
      if (bp != NULL)
        break;
    }
    size = size >> 1;
    list++;
  }

  //If no fit was found, get more memory and palce the block in it.
  if (bp == NULL)
  {
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize)) == NULL)
      return NULL;
  }
  place(bp, asize);
  return bp;
}

//
//
// Practice problem 9.9
//
// place - Place block of asize bytes at start of free block bp 
//         and split if remainder would be at least minimum block size
//
static void place(void *bp, size_t asize)
{
  size_t csize = GET_SIZE(HDRP(bp));
  size_t size_operation = csize - asize;
  delete_node(bp);//DELETE block from list

  if (size_operation >= MINSIZE)//split!
  {
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    PUT_NOTAG(HDRP(NEXT_BLKP(bp)), PACK(size_operation, 0));
    PUT_NOTAG(FTRP(NEXT_BLKP(bp)), PACK(size_operation, 0));
    insert_node(NEXT_BLKP(bp), size_operation);
  }
  else//NO SPLIT!
  {
    PUT(HDRP(bp), PACK(csize, 1));
    PUT(FTRP(bp), PACK(csize, 1));
  }
  return;
}

//
// mm_realloc -- implemented for you
//
void *mm_realloc(void *ptr, size_t size)
{
  void *newp = ptr;
  size_t copySize = size;
  int remainder;
  int enlarge_size;
  int buffer_block; 

  if (size == 0)//erase invalid blocks. 
    return NULL;

  if (copySize <= DSIZE){ //adjusting the block regarding boundary tag and alignment
    copySize = 2 * DSIZE;
  }
  else {
    copySize = DSIZE * ((copySize + (DSIZE)+(DSIZE - 1)) / DSIZE);
  }

  copySize += BUFFER;
  
  buffer_block = GET_SIZE(HDRP(ptr)) - copySize;//block buffer.

  if (buffer_block < 0){//allow more space if overhead is smaller than minimum
    //checking if the next block is free or last.
    if (!GET_ALLOC(HDRP(NEXT_BLKP(ptr))) || !GET_SIZE(HDRP(NEXT_BLKP(ptr)))) {
      remainder = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr))) - copySize;
      if (remainder < 0) {
        enlarge_size = MAX(-remainder, CHUNKSIZE);
        if (extend_heap(enlarge_size) == NULL)
          return NULL;
        remainder += enlarge_size;
      }

      delete_node(NEXT_BLKP(ptr));
      PUT_NOTAG(HDRP(ptr), PACK(copySize + remainder, 1));
      PUT_NOTAG(FTRP(ptr), PACK(copySize + remainder, 1));
    }
    else {
      newp = mm_malloc(copySize - DSIZE);
      memmove(newp, ptr, MIN(size, copySize));
      mm_free(ptr);
    }
    buffer_block = GET_SIZE(HDRP(newp)) - copySize;
  }
  if (buffer_block < 2 * BUFFER)
    TAG_SET(HDRP(NEXT_BLKP(newp)));
  return newp;
}

//
// mm_checkheap - Check the heap for consistency 
//

/*void mm_checkheap(int verbose)
{
  //
  // This provided implementation assumes you're using the structure
  // of the sample solution in the text. If not, omit this code
  // and provide your own mm_checkheap
  //
  void *bp = heap_listp;

  if (verbose) {
    printf("Heap (%p):\n", heap_listp);
  }

  if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
    printf("Bad prologue header\n");
  }
  checkblock(heap_listp);

  for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
    if (verbose)  {
      printblock(bp);
    }
    checkblock(bp);
  }

  if (verbose) {
    printblock(bp);
  }

  if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) {
    printf("Bad epilogue header\n");
  }
}
*/

/*static void printblock(void *bp)
{
  size_t hsize, halloc, fsize, falloc;

  hsize = GET_SIZE(HDRP(bp));
  halloc = GET_ALLOC(HDRP(bp));
  fsize = GET_SIZE(FTRP(bp));
  falloc = GET_ALLOC(FTRP(bp));

  if (hsize == 0) {
    printf("%p: EOL\n", bp);
    return;
  }

  printf("%p: header: [%d:%c] footer: [%d:%c]\n",
    bp,
    (int)hsize, (halloc ? 'a' : 'f'),
    (int)fsize, (falloc ? 'a' : 'f'));
}
*/
/*
static void checkblock(void *bp)
{
  if ((size_t)bp % 8) {
    printf("Error: %p is not doubleword aligned\n", bp);
  }
  if (GET(HDRP(bp)) != GET(FTRP(bp))) {
    printf("Error: header does not match footer\n");
  }
}
*/

//source github He (Henry) Tian
static void insert_node(void *bp, size_t size)
{
  int list = 0;
  void *search_pointer = bp;
  void *insert_pointer = NULL;
  while ((list < LISTS - 1) && (size > 1))
  {
    size = size >> 1;
    list++;
  }
  search_pointer = working_lists[list];
  while ((search_pointer != NULL) && (size > GET_SIZE(HDRP(search_pointer)))) 
  //choose where to insert pointer in the list and keep this list in ascending order.
  {
    insert_pointer = search_pointer;
    search_pointer = PREDEC(search_pointer);
  }
  if (search_pointer != NULL) 
  {
    if (insert_pointer != NULL) 
    {
      SET_POINTER(PRED_PTR(bp), search_pointer);
      SET_POINTER(SUCCESS_PTR(search_pointer), bp);
      SET_POINTER(SUCCESS_PTR(bp), insert_pointer);
      SET_POINTER(PRED_PTR(insert_pointer), bp);
    }
    else 
    {
      SET_POINTER(PRED_PTR(bp), search_pointer);
      SET_POINTER(SUCCESS_PTR(search_pointer), bp);
      SET_POINTER(SUCCESS_PTR(bp), NULL);
      working_lists[list] = bp;//add block to the correct list
    }
  }
  else 
  {
    if (insert_pointer != NULL) 
    {
      SET_POINTER(PRED_PTR(bp), NULL);
      SET_POINTER(SUCCESS_PTR(bp), insert_pointer);
      SET_POINTER(PRED_PTR(insert_pointer), bp);
    }
    else {
      SET_POINTER(PRED_PTR(bp), NULL);
      SET_POINTER(SUCCESS_PTR(bp), NULL);

      /* Add block to appropriate list */
      working_lists[list] = bp;
    }
  }

  return;
}

//source github He (Henry) Tian
static void delete_node(void *bp)
{
  int list = 0;
  size_t size = GET_SIZE(HDRP(bp));
  while ((list < LISTS - 1) && (size > 1)){
    size >>= 1;
    list++;
  }
  if (PREDEC(bp) != NULL) {
    if (SUCCESS(bp) != NULL) {
      SET_POINTER(SUCCESS_PTR(PREDEC(bp)), SUCCESS(bp));
      SET_POINTER(PRED_PTR(SUCCESS(bp)), PREDEC(bp));
    }
    else {
      SET_POINTER(SUCCESS_PTR(PREDEC(bp)), NULL);
      working_lists[list] = PREDEC(bp);
    }
  }
  else {
    if (SUCCESS(bp) != NULL){
      SET_POINTER(PRED_PTR(SUCCESS(bp)), NULL);
    }
    else {
      working_lists[list] = NULL;
    }
  }
  return;
}