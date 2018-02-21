#include <iostream>
#include <json.hpp>

#include "sign-modal.h"
#include "sign-modal.js.h"

#include "components/modals/modals.h"

#include "common/logger/logger.h"
#include "common/web-ui/web-ui.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;

/**
 * @brief Definizione SignModal, modale per registrarsi
 * @file sign-modal.cc
 */

namespace Modals { 

    namespace SignModal {

        /** Nome identificativo del modale signup */
        static const string modalRef = "sign-modal";

        static const string SIGN_DESTROY = "modals.SignModal.destroy()";

        namespace Events { 

            void Show() {
                Modals::Events::ShowModalByRef(modalRef);  
            }

            void Hide() {
                Modals::Events::HideModalByRef(modalRef);    
            }            
        }

        void RegisterModal() {
            log_base(TAG::CMP, "Modals::SignModal::RegisterModal", "");

            WebUI::Execute(_src_components_modal_sign_modal_sign_modal_js);
        }

        void EraseModal () {
            log_base(TAG::CMP, "Modals::SignModal::EraseModal", "");

            WebUI::Execute(SIGN_DESTROY);
        }
        
    }
}