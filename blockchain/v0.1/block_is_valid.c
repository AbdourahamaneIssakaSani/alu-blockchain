#include "blockchain.h"


/**
* block_is_valid - checks if a Block is valid
*
* @block: pointer to the Block to check
* @prev_block: pointer to the previous Block
*
* Return: 0 if the Block is valid, 1 if it is invalid
*/
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	block_t const _genesis = GENESIS_BLOCK;

	block_t const *_prev_block = prev_block ? prev_block : &_genesis;

	if (!block || !prev_block)
		return (1);
	if (block->info.index != _prev_block->info.index + 1)
		return (1);
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(_prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (!block_hash(_prev_block, hash_buf) ||
		memcmp(hash_buf, _prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	return (0);
}
