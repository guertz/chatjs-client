#include <iostream>
#include <json.hpp>

#include "conn-modal.h"
#include "conn-modal.js.h"

#include "components/modals/modals.h"

#include "common/logger/logger.h"
#include "common/web-ui/web-ui.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;

/**
 * @brief Definizione ConnModal, modale per gestire errori di connessione
 * @file conn-modal.cc
 */

namespace Modals { 

    namespace ConnModal {

        /** Nome identificativo del modale conn */
        static const string modalRef = "conn-modal";

        static const string CONN_DESTROY = "modals.ConnModal.destroy()";

        namespace Events { 

            void Show() {
                Modals::Events::ShowModalByRef(modalRef);  
            }

            void Hide() {
                Modals::Events::HideModalByRef(modalRef);    
            }            
        }

        void RegisterModal() {
            log_base(TAG::CMP, "Modals::ConnModal::RegisterModal", "");

            WebUI::Execute(_src_components_modal_conn_modal_conn_modal_js);
        }

        void EraseModal () {
            log_base(TAG::CMP, "Modals::ConnModal::EraseModal", "");

            WebUI::Execute(CONN_DESTROY);
        }

    }
}