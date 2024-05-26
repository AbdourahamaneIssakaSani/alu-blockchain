#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <llist.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>
#include <sys/types.h>

#include <openssl/sha.h>
#include "../../crypto/hblk_crypto.h"
#include "provided/endianness.h"
#include "transaction/transaction.h"

#include <time.h>

#define BLOCKCHAIN_DATA_MAX 1024
#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.3"


/**
* struct blockchain_s - Blockchain structure
*
* @chain: Linked list of pointers to block_t
*/
typedef struct blockchain_s
{
	llist_t     *chain;
} blockchain_t;

/**
* struct block_info_s - Block info structure
*
* @index:      Index of the Block in the Blockchain
* @difficulty: Difficulty of proof of work (hash leading zero bits)
* @timestamp:  Time the Block was created at (UNIX timestamp)
* @nonce:      Salt value used to alter the Block hash
* @prev_hash:  Hash of the previous Block in the Blockchain
*/
typedef struct block_info_s
{
	/*
	* The order of the elements in this structure should remain the same.
	* It was designed so every element of this structure is aligned and
	* doesn't require padding from the compiler.
	* Therefore, it is possible to use the structure as an array of char,
	* on any architecture.
	*/
	uint32_t    index;
	uint32_t    difficulty;
	uint64_t    timestamp;
	uint64_t    nonce;
	uint8_t     prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;


/**
* struct block_data_s - Block data
*
* @buffer: Data buffer
* @len:    Data size (in bytes)
*/
typedef struct block_data_s
{
	/*
	* @buffer must stay first, so we can directly use the structure as
	* an array of char
	*/
	int8_t      buffer[BLOCKCHAIN_DATA_MAX];
	uint32_t    len;
} block_data_t;

/**
* struct block_s - Block structure
*
* @info:         Block info
* @data:         Block data
* @transactions: List of transactions
* @hash:         256-bit digest of the Block, to ensure authenticity
*/
typedef struct block_s
{
	block_info_t    info; /* This must stay first */
	block_data_t    data; /* This must stay second */
	llist_t     *transactions;
	uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
* struct hblk_file_s - Block file format
* @hblk_magic: magic bytes for HBLK
* @hblk_version: blockchain version
* @hblk_endian: endianness, 1 if big endian, 2 if little endian
* @hblk_blocks: number of blocks in the file
*/
typedef struct hblk_file_s
{
	int8_t      hblk_magic[4];
	int8_t      hblk_version[3];
	int8_t      hblk_endian;
	int32_t     hblk_blocks;
} hblk_file_t;

blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev,

int8_t const *data, uint32_t data_len);

void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block,

uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);

blockchain_t *blockchain_deserialize(char const *path);

int block_is_valid(block_t const *block, block_t const *prev_block);

void _blockchain_destroy(blockchain_t *blockchain);
void _blockchain_print(blockchain_t const *blockchain);

#endif /* BLOCKCHAIN_H */
