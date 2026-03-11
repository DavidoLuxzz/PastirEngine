#pragma once
#ifndef __DIALOGBOX_HPP
#define __DIALOGBOX_HPP

#include <string>
#include <animation.hpp>

#define MAX_DIALOG_PAGES 10
#define NUM_GAME_DIALOGS 2
#define MODIFIABLE_DIALOG_ID 0

namespace dialogbox {
    struct dialog_t {
        int numPages;
        std::string *pages;

        constexpr inline dialog_t(){}
        dialog_t(const dialog_t&) = delete;
        void operator=(const dialog_t& d) = delete;

        inline dialog_t(int numPg) : numPages(numPg) {
            alloc(numPg);
        }
        inline std::string& operator[](int i) {
            return pages[i];
        }
        inline ~dialog_t() {
            delete[] pages;
        }
        inline dialog_t& alloc(size_t size) {
            numPages = size;
            pages = new std::string[size];
            return *this;
        }
    };

    /**
     * Initializes the dialog box.
     * Uglavnom Loads texture i init sve dialoge.
     */
    int init();
    /// Will be defined in dialogs.cpp
    void _loadDialogs(dialog_t* out_dialogs);

    void show(bool t=true);
    void hide();
    bool isShowing();

    void setText(const std::string);
    void setDialog(int);
    const dialog_t& getDialog(int dialogID);

    void draw();
    void _update();
} // namespace dialogbox


#endif