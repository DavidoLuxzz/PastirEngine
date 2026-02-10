#pragma once
#ifndef __ASSET_MANAGER_HPP
#define __ASSET_MANAGER_HPP

#include <string>

namespace assman {
    std::string getcwd();
    std::string getasset(std::string&&);
    std::string getasset(const char*);
    /**
     * Sets the current working directory path.
     * @param path the path to directory
     * @return 0 if success, otherwise an error has occurred
     */
    int setcwd(const char* path);
    int setcwd(const std::string&);
    /// @brief setcwd(base+add);
    /// @param base base path
    /// @param add string that gets appened to base path
    /// @return 0 if success
    int setcwd_(const char* base, const char* add);
    /// @brief al_get_standard_path(allegro_path_id)
    /// @param allegro_path_id allegro path id
    /// @param error Nullable
    /// @return the path duh
    std::string getallegropathstr(int allegro_path_id, int* error);
    /// @brief Returns the path to the running executable
    /// @return path to exec
    std::string getexecpath();
} // namespace assman


#endif