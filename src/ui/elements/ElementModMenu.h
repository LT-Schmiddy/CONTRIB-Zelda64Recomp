#ifndef RECOMPUI_ELEMENT_MOD_MENU_H
#define RECOMPUI_ELEMENT_MOD_MENU_H

#include "common.h"

namespace recompui {

class ElementModMenu : public Rml::Element {
public:
	ElementModMenu(const Rml::String& tag);
	virtual ~ElementModMenu();

	void open_menu();
};

ElementModMenu *get_mod_menu(Rml::ElementDocument *doc);

} // namespace recompui
#endif
