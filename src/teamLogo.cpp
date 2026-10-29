#include "robodash/api.h"

extern "C" {
    extern const lv_img_dsc_t logo;
}

rd::Image teamLogo(&logo, "Team Logo");

void showTeamLogo() {
    teamLogo.focus();
}