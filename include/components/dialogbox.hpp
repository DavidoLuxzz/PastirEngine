#pragma once
#ifndef __DIALOGBOX_HPP
#define __DIALOGBOX_HPP

#include <string>

#define MAX_DIALOG_PAGES 10

namespace dialogbox {
    struct dialog_t {
        int numPages;
        std::string *pages;

        dialog_t() = delete;
        dialog_t(const dialog_t&) = delete;
        void operator=(const dialog_t& d) = delete;

        inline dialog_t(int numPg) : numPages(numPg) {
            pages = new std::string[numPg];
        }
        inline std::string& operator[](int i) {
            return pages[i];
        }
        inline ~dialog_t() {
            delete[] pages;
        }
    };

    /**
     * Initializes the dialog box.
     * Uglavnom Loads texture
     */
    int init();

    void show(bool t=true);
    void hide();
    bool isShowing();

    void setText(const std::string);
    void setDialog(const dialog_t&);

    void draw();
} // namespace dialogbox


#endif