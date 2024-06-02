#include "blockchain.h"

/**
 * block_mine - mines a block with requisite difficulty
 * @block: pointer to block to mine
 */
void block_mine(block_t *block)
{
	uint8_t buff[SHA256_DIGEST_LENGTH];

	if ((!block) || (block->info.difficulty == 0))
		return;

	block_hash(block, block->hash);

	for (;;)
	{
		block->info.nonce++;
		block_hash(block, buff);
		if (hash_matches_difficulty(buff, block->info.difficulty))
		{
			memcpy(block->hash, buff, SHA256_DIGEST_LENGTH);
			break;
		}
	}
}
