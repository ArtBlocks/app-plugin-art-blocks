#include "art_blocks_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    msg->uiType = ETH_UI_TYPE_GENERIC;
    artblock_parameters_t *context = (artblock_parameters_t *) msg->pluginContext;
    switch (context->selectorIndex) {
        case PURCHASE:
            msg->numScreens = 1; // <-- 1 arg to function
            break;
        case PURCHASE_TO:
            msg->numScreens = 2; // <-- 2 args to function
            break;
        case CREATE_BID:
            msg->numScreens = 1; // <-- 1 arg to function
            break;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
