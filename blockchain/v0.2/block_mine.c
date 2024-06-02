#include "blockchain.h"

/**
 * block_mine - mines a block with requisite difficulty
 * @block: pointer to block to mine
 */
void block_mine(block_t *block)
{
	if (!block)
		return;
	block->info.nonce = 0;
	while (hash_matches_difficulty(block_hash(block, block->hash),
				       block->info.difficulty) != 1)
		block->info.nonce++;
}
