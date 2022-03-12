#include <iostream>
#include "socialnetwork.h"

int main(char* ar[], int count)
{
    SocialNetwork sn;

    sn.addnewMan("Oleg");
    sn.addnewMan("Kostya");
    sn.addnewMan("Misha");
    sn.addnewMan("Vika");
    sn.addnewMan("Lesha");

    sn.delMan("Vika");
    sn.addnewMan("Anya");

    sn.addFriendship("Oleg", "Kostya");
    sn.addFriendship("Kostya", "Misha");
    sn.addFriendship("Misha", "Anya");
    sn.addFriendship("Anya", "Lesha");

    sn.showThreeHandshakes();

    return 0;
}
