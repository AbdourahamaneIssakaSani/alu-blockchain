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

	block_t genesis_block = {
		{ /* info */
			972, /* index */
			98, /* difficulty */
			1537578000, /* timestamp */
			94104, /* nonce */
			"\xdb\x74\xc9\x40\xd4\x47\xe8\x77\xd1\x19\xdf\x61\x3e\xdd\x27\x00\xc4"
			"\xa8\x4c\xd1\xcf\x08\xbe\xb7\xcb\xc3\x19\xbc\xfa\xea\xb9\x7a" /* prev */
		},
		{ /* data */
			"Holberton School", /* buffer */
			16 /* len */
		},
		{0} /* hash */
	};


	block_t const _genesis = genesis_block;

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
