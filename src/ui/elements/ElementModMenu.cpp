#include "ElementModMenu.h"
#include "presets.h"
#include "librecomp/mods.hpp"

#include <string>

namespace recompui {

static const std::string mod_menu_id = "mod-menu";
static const std::string mod_menu_button_id = "mod-menu__button";
static const std::string mod_menu__close_button_id = "mod-menu__close-button";
static const std::string mod_menu_mod_id_base = "mod-menu__mod"; // + index

static const BEM mod_menu_bem("mod-menu");

static const std::string cls_base = mod_menu_bem.get_block(); 
static const std::string cls_modal_wrapper = mod_menu_bem.el("modal-wrapper"); 
static const std::string cls_modal_header = mod_menu_bem.el("modal-header"); 
static const std::string cls_modal_body = mod_menu_bem.el("modal-body"); 
static const std::string cls_list = mod_menu_bem.el("list"); 
static const std::string cls_list_scroll = mod_menu_bem.el("list-scroll"); 
static const std::string cls_details = mod_menu_bem.el("details"); 

static Rml::Element *add_div_with_class(Rml::ElementDocument *doc, Rml::Element *parent_el, const std::string& cls) {
    Rml::Element *el = parent_el->AppendChild(doc->CreateElement("div"));
    el->SetClass(cls.c_str(), true);
    return el;
}

const std::string get_mod_nav_up_id(int index) {
    if (index == 0) {
        return "#" + mod_menu_button_id;
    } else {
        return "#" + mod_menu_mod_id_base + std::to_string(index - 1);
    }
}
const std::string get_mod_nav_down_id(int index, size_t num_mods) {
    if (index == num_mods - 1) {
        return "#" + mod_menu_button_id;
    } else {
        return "#" + mod_menu_mod_id_base + std::to_string(index + 1);
    }
}

// treated as its own class root
static const BEM mod_menu_mod("mod-menu-mod");
static Rml::Element *add_mod_menu_mod(
    Rml::ElementDocument *doc,
    Rml::Element *parent_el,
    recomp::mods::ModDetails &mod,
    int index,
    size_t num_mods
) {
    Rml::Element *mod_el = parent_el->AppendChild(doc->CreateElement("label"));

    mod_el->SetClass(mod_menu_mod.get_block(), true);
    // mod_el->SetProperty("nav-up", get_mod_nav_up_id(index));
    // mod_el->SetProperty("nav-down", get_mod_nav_down_id(index, num_mods));
    // mod_el->SetId(mod_menu_mod_id_base + std::to_string(index));

    {
        auto span = mod_el->AppendChild(doc->CreateElement("span"));
        span->SetInnerRML(mod.mod_id);
        span->SetClass(mod_menu_mod.el("label"), true);

        auto toggle = add_icon_button(doc, mod_el, "icons/Plus.svg", ButtonVariant::Primary);
        toggle->SetProperty("nav-up", get_mod_nav_up_id(index));
        toggle->SetProperty("nav-down", get_mod_nav_down_id(index, num_mods));
        toggle->SetProperty("nav-left", "none");
        toggle->SetProperty("nav-right", "none");
        toggle->SetId(mod_menu_mod_id_base + std::to_string(index));
    }

    return mod_el;
}

ElementModMenu::ElementModMenu(const Rml::String& tag) : Rml::Element(tag)
{
    SetAttribute("recomp-store-element", true);
    Rml::ElementDocument *doc = GetOwnerDocument();
    SetClass(mod_menu_bem.block, true);
    SetId(mod_menu_id);

    std::vector<recomp::mods::ModDetails> mods = recomp::mods::get_mod_details("mm");
    size_t num_mods = mods.size();

    {
        Rml::Element *modal_wrapper_el = add_div_with_class(doc, this, cls_modal_wrapper);
        {
            Rml::Element *header_el = add_div_with_class(doc, modal_wrapper_el, cls_modal_header);
            {
                auto button = add_button(doc, header_el, "Refresh", ButtonVariant::Primary);
                button->SetId(mod_menu_button_id);
                const std::string below_item = num_mods > 0 ? "#" + mod_menu_mod_id_base + "0" : "#" + mod_menu_button_id;
                const std::string above_item = num_mods > 0 ? "#" + mod_menu_mod_id_base + std::to_string(num_mods - 1) : "#" + mod_menu_button_id;
                button->SetProperty("nav-down", below_item);
                button->SetProperty("nav-up", above_item);
                button->SetProperty("nav-left", "#" + mod_menu__close_button_id);
                button->SetProperty("nav-right", "#" + mod_menu__close_button_id);

                auto close_button = add_icon_button(doc, header_el, "icons/X.svg", ButtonVariant::Tertiary);
                close_button->SetId(mod_menu__close_button_id);
                close_button->SetProperty("nav-down", below_item);
                close_button->SetProperty("nav-up", above_item);
                close_button->SetProperty("nav-left", "#" + mod_menu_button_id);
                close_button->SetProperty("nav-right", "#" + mod_menu_button_id);
            }

            Rml::Element *body_el = add_div_with_class(doc, modal_wrapper_el, cls_modal_body);
            {
                Rml::Element *list_el = add_div_with_class(doc, body_el, cls_list);
                {
                    Rml::Element *list_el_scroll = add_div_with_class(doc, list_el, cls_list_scroll);
                    {
                        int i = 0;
                        for (auto& mod : mods) {
                            add_mod_menu_mod(doc, list_el_scroll, mod, i, num_mods);
                            i++;
                        }
                    } // list_el_scroll
                } // list_el

                Rml::Element *details_el = add_div_with_class(doc, body_el, cls_details);
                details_el->SetInnerRML("two");
            }
        }
    }
}

ElementModMenu::~ElementModMenu()
{
}

void ElementModMenu::open_menu() {
    SetClass(mod_menu_bem.mod("open"), true);
    auto button = GetElementById(mod_menu_button_id);
    if (button != nullptr) {
        button->Focus();
    }
}

ElementModMenu *get_mod_menu(Rml::ElementDocument *doc) {
    return (ElementModMenu *)doc->GetElementById(mod_menu_id);
}



} // namespace Rml
