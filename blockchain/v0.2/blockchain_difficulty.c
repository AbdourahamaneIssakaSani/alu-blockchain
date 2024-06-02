#include "blockchain.h"


/**
* blockchain_difficulty - adjust difficulty for next block of blockchain
* @blockchain: pointer to working blockchain
* Return: adjusted difficulty
*/
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *last_block, *adjusted_block;
	uint64_t expected_time, actual_time;
	uint32_t new_difficulty;

	if (!blockchain)
		return (0);

	last_block = llist_get_tail(blockchain->chain);
	if (!last_block)
		return (0);

	if (last_block->info.index == 0 ||
		last_block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL)
		return (last_block->info.difficulty);

	expected_time = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
	actual_time = last_block->info.timestamp - ((block_t *)llist_get_node_at(
	blockchain->chain, last_block->info.index - DIFFICULTY_ADJUSTMENT_INTERVAL
))->info.timestamp;

	if (actual_time < expected_time / 2)
		new_difficulty = last_block->info.difficulty + 1;
	else if (actual_time > expected_time * 2)
	new_difficulty = last_block->info.difficulty > 0 ?
	last_block->info.difficulty - 1 :
	0;
	else
		new_difficulty = last_block->info.difficulty;

	adjusted_block = block_create(llist_get_tail(blockchain->chain), NULL, 0);
	if (!adjusted_block)
		return (0);

	adjusted_block->info.difficulty = new_difficulty;
	if (!block_is_valid(adjusted_block, last_block))
		new_difficulty = last_block->info.difficulty;

	free(adjusted_block);
	return (new_difficulty);
}
