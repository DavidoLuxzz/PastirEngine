#include <asset_manager.hpp>
#include <allegro5/allegro.h>
#include <filesystem>

#define ASSMAN_LOG_PREFIX "[ASSMAN] "

#define ASSMAN_SUCCESS_STR "No error"
#define ASSMAN_DIR_DOESNT_EXISTS_STR "Working directory doesn't exists"
#define ASSMAN_PATH_DOESNT_EXISTS_STR "Unable to find path"
#define ASSMAN_ALLEGRO_STANDARD_PATH_PROBLEM_STR "error: al_get_standard_path(id)"
#define ASSMAN_IS_NOT_A_DIR_STR "Not a directory"

#define ASSMAN_LOG(errorstr) printf("%s%s\n",ASSMAN_LOG_PREFIX,errorstr)
#define ASSMAN_LOG_PATH(errorstr,path) printf("%s%s [%s]\n",ASSMAN_LOG_PREFIX,errorstr,path)

namespace assman {
    std::string cwd;
}

std::string assman::getcwd() {
    return cwd;
}
std::string assman::getasset(std::string&& file) {
    if (file.starts_with('/')) return cwd+file.substr(1);
    return cwd+file;
}
std::string assman::getasset(const char* file) {
    return getasset(std::string(file));
}

int assman::setcwd(const char* path) {
    if (!std::filesystem::exists(path)) ASSMAN_LOG_PATH(ASSMAN_DIR_DOESNT_EXISTS_STR, path);
    cwd = path;
    if (!cwd.ends_with('/')) cwd.append("/");
    return !al_change_directory(path);
}
int assman::setcwd(const std::string& path) {
    return setcwd(path.c_str());
}
int assman::setcwd_(const char* base, const char* add) {
    std::string path(base);
    path += add;
    return setcwd(path.c_str());
}
std::string assman::getallegropathstr(int id, int* error) {
    ALLEGRO_PATH* path = al_get_standard_path(id);
    if (!path) {
        ASSMAN_LOG(ASSMAN_ALLEGRO_STANDARD_PATH_PROBLEM_STR);
        if (error) *error = -1;
    } else if (error) *error = 0;
    std::string pathstr(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP));
    al_destroy_path(path); // u docs pise da bi trebalo ovo da se uradi posle al_get_standard_path
    return pathstr;
}
std::string assman::getexecpath() {
    return getallegropathstr(ALLEGRO_EXENAME_PATH, NULL); // napisace error
}
