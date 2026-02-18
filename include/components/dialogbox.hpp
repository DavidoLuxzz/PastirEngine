#pragma once
#ifndef __DIALOGBOX_HPP
#define __DIALOGBOX_HPP

namespace dialogbox {
    /**
     * Initializes the dialog box.
     * Uglavnom Loads texture
     */
    int init();

    void show(bool t=true);
    void hide();
    bool isShowing();

    void draw();
} // namespace dialogbox


#endif