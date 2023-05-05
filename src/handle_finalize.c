#include "art_blocks_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    msg->uiType = ETH_UI_TYPE_GENERIC;
    artblock_parameters_t *context = (artblock_parameters_t *) msg->pluginContext;
    switch (context->selectorIndex) {
        case PURCHASE:
            msg->numScreens = 1;
            break;
        case PURCHASE_HOLDER:
            msg->numScreens = 3;
            break;
        case PURCHASE_MERKLE:
            msg->numScreens = 2;
            break;
        case PURCHASE_TO:
            msg->numScreens = 2;
            break;
        case PURCHASE_TO_HOLDER:
            msg->numScreens = 4;
            break;
        case PURCHASE_TO_MERKLE:
            msg->numScreens = 3;
            break;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
