#ifndef RECOMPUI_ELEMENTS_H
#define RECOMPUI_ELEMENTS_H

#include "recomp_ui.h"
#include "RmlUi/Core/Element.h"

#include "elements/ElementConfigOption.h"
#include "elements/ElementConfigGroup.h"
#include "elements/ElementOptionTypeButton.h"
#include "elements/ElementOptionTypeCheckbox.h"
#include "elements/ElementOptionTypeColor.h"
#include "elements/ElementOptionTypeDropdown.h"
#include "elements/ElementOptionTypeRadioTabs.h"
#include "elements/ElementOptionTypeRange.h"
#include "elements/ElementOptionTypeTextField.h"
#include "elements/ElementDescription.h"
#include "elements/ElementModMenu.h"

namespace recompui {
    void register_custom_elements();

    Rml::ElementInstancer* get_custom_element_instancer(std::string tag);
}

#endif
