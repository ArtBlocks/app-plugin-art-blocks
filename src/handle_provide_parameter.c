#include "art_blocks_plugin.h"

static void handle_address_to(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    memset(context->address_to, 0, sizeof(context->address_to));
    memcpy(context->address_to, &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH], ADDRESS_LENGTH);
    printf_hex_array("Address To: ", ADDRESS_LENGTH, context->address_to);
}

static void handle_merkle_proof(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    memset(context->merkle_proof, 0, sizeof(context->address_to));
    memcpy(context->merkle_proof,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           ADDRESS_LENGTH);
    printf_hex_array("Merkle Proof: ", ADDRESS_LENGTH, context->merkle_proof);
}

static void handle_owned_nft_address(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    memset(context->owned_nft_address, 0, sizeof(context->address_to));
    memcpy(context->owned_nft_address,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           ADDRESS_LENGTH);
    printf_hex_array("Owned NFT Contract: ", ADDRESS_LENGTH, context->owned_nft_address);
}

static void handle_owned_nft_id(ethPluginProvideParameter_t *msg,
                                     artblock_parameters_t *context) {
    memset(context->owned_nft_id, 0, sizeof(context->address_to));
    memcpy(context->owned_nft_id,
           &msg->parameter[PARAMETER_LENGTH - sizeof(context->address_to)],
           sizeof(context->address_to));
    printf_hex_array("Owned NFT ID: ", sizeof(context->address_to), context->owned_nft_id);
}

static void handle_merkle_minter(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    switch (context->next_param) {
        case ADDRESS_TO:
            handle_merkle_proof(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_holder_minter(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    switch (context->next_param) {
        case ADDRESS_HOLDER:
            handle_owned_nft_address(msg, context);
            context->next_param = TOKEN_ID_HOLDER;
            break;
        case TOKEN_ID_HOLDER:
            handle_owned_nft_id(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_purchase_to(ethPluginProvideParameter_t *msg, artblock_parameters_t *context) {
    switch (context->next_param) {
        case ADDRESS_TO:
            handle_address_to(msg, context);
            context->next_param = NONE;
            break;
        case ADDRESS_HOLDER:
            handle_holder_minter(msg, context);
            break;
        case MERKLE_PROOF:
            handle_merkle_minter(msg, context);
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    artblock_parameters_t *context = (artblock_parameters_t *) msg->pluginContext;

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case PURCHASE:
            break;
        case PURCHASE_HOLDER:
            handle_holder_minter(msg, context);
            break;
        case PURCHASE_MERKLE:
            handle_merkle_minter(msg, context);
            break;
        case PURCHASE_TO:
            handle_purchase_to(msg, context);
            break;
        case PURCHASE_TO_HOLDER:
            handle_purchase_to(msg, context);
            break;
        case PURCHASE_TO_MERKLE:
            handle_purchase_to(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
