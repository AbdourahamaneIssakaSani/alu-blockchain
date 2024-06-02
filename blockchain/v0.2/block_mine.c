#include "blockchain.h"


/**
* block_mine - mines a block with requisite difficulty
* @block: pointer to block to mine
*/
void block_mine(block_t *block)
{
	uint64_t nonce = 0;
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};

	do {
		block->info.nonce = nonce;
		block_hash(block, hash_buf);
		nonce++;
	} while (!hash_matches_difficulty(hash_buf, block->info.difficulty));
}
