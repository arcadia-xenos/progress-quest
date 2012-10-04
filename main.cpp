#include <QtGui/QApplication>
#include "mainwindow.h"
/*
  Progress Quest (ver7, c++/Qt version)
  Martin Horner (xeno@morgoth.net) - Sep 2012

  This software owes a great debt to Eric Fredricksen and his original
  Progress Quest written in Delphi pascel also the subsequient javascript
  version.

  Progress Quest started (if I understand correctly) as a joke. A sort of
  internet meme that went out of control. If I interpret the joke correctly
  (and I certianly might not), Eric was pointing out that most MMORPG's
  (RPG's?) are just time consumption. There were certinly other aspects to
  the joke, but I think that was the main point.

  I had already observed that the major commodity in MMO's was player time.
  When I found PQ a few years back, I didn't yet realize that PQ is (beside
  being a great joke), the logical conclusion to the problem of the "casual
  player" problem in MMORPG's. Take the player out of the game!

  It also serves as a great baseline for the problems involved with creating
  interesting RPG's on hand-held touch devices. With only very limited
  interaction available to the player, the game must be in itself interesting
  to just watch.

  However to be used as a starting point or framework for such novel uses, I
  decided to try to re-write the core features as a c++ program. A friend (Edz)
  put me onto using Qt as a framework and development took off. With Eric's
  unique joke and more than a little of Edz help, the exploration of the
  concepts of Zero-Player and Near Zero-Player RPG fun are off and running.
*/

int main(int argc, char *argv[])
{

    /*
      This block produced by qt creator for manageing ui
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // start event loop
    return a.exec();
}

