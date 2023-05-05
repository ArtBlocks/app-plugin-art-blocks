#pragma once

#include <string.h>
#include "eth_internals.h"
#include "eth_plugin_interface.h"

#define NUM_SELECTORS    6
#define PLUGIN_NAME      "ArtBlocks"
#define SELECTOR_SIZE    4
#define PARAMETER_LENGTH 32
#define RUN_APPLICATION  1

// Plugin uses 0x00000 as a dummy address to reprecent ETH.
extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];

#define ADDRESS_IS_NETWORK_TOKEN(_addr) (!memcmp(_addr, NULL_ETH_ADDRESS, ADDRESS_LENGTH))
typedef enum {
    PURCHASE,
    PURCHASE_HOLDER,
    PURCHASE_MERKLE,
    PURCHASE_TO,
    PURCHASE_TO_HOLDER,
    PURCHASE_TO_MERKLE,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    AMOUNT,
    NONE,
} parameter;

typedef enum {
    AMOUNT_SCREEN,
    ADDRESS_TO_SCREEN,
    ADDRESS_HOLDER_SCREEN,
    TOKEN_ID_HOLDER_SCREEN,
    ERROR,
} screens_t;

#define ADDRESS_TO      0
#define ADDRESS_HOLDER  1
#define TOKEN_ID_HOLDER 2
#define MERKLE_PROOF    3
#define NONE            4

extern const uint8_t *const ART_BLOCKS_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct artblocks_parameters_t {
    // For display.
    uint8_t address_to[ADDRESS_LENGTH];
    uint8_t contract_address_sent[ADDRESS_LENGTH];
    char ticker_sent[MAX_TICKER_LEN];
    uint8_t merkle_proof[PARAMETER_LENGTH];
    uint8_t owned_nft_address[ADDRESS_LENGTH];
    uint32_t owned_nft_id;

    // For parsing data.
    uint8_t next_param;

    // For both parsing and display.
    selector_t selectorIndex;
} artblock_parameters_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(artblock_parameters_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_query_contract_id(void *parameters);

static inline void printf_hex_array(const char *title __attribute__((unused)),
                                    size_t len __attribute__((unused)),
                                    const uint8_t *data __attribute__((unused))) {
    PRINTF(title);
    for (size_t i = 0; i < len; ++i) {
        PRINTF("%02x", data[i]);
    };
    PRINTF("\n");
}