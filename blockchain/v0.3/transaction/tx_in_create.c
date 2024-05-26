#include "transaction.h"


/**
* tx_in_create - creates a transaction input structure
*
* @unspent:	unspent transaction output to be converted to transaction input
*
* Return: a new transaction input structure
*/
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *tx_in;

	if (!unspent)
		return (NULL);

	tx_in = calloc(1, sizeof(*tx_in));
	if (!tx_in)
		return (NULL);

	memcpy(tx_in, &unspent->out, sizeof(unspent->out));
	if (!sha256((int8_t const *)tx_in, sizeof(tx_in->block_hash) +
	sizeof(tx_in->tx_id) + sizeof(tx_in->tx_out_hash) +
	sizeof(tx_in->sig), tx_in->tx_out_hash))
	{
		free(tx_in);
		return (NULL);
	}

	return (tx_in);
}
