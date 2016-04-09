# GConjugue

The application conjugates Portuguese verbs as spoken in Brazil:

![Screenshot](https://raw.githubusercontent.com/jalvesaq/gconjugue/master/screenshot_pt.png "Screenshot")

When the entered expression is not a verb, GConjugue tries to find it among
the conjugated forms of known verbs, as below:

![Screenshot](https://raw.githubusercontent.com/jalvesaq/gconjugue/master/screenshot_en.png "Screenshot")

It also has the option of conjugating verbs as ordinary Brazilians do. In
fact, Brazilians of different regions deviate from the normative grammar in
different ways, but the conjugation displayed will already help foreigners to
grasp what Brazilians are saying:

![Screenshot](https://raw.githubusercontent.com/jalvesaq/gconjugue/master/screenshot_br.png "Screenshot")

If you are using Debian, Ubuntu or another Debian based distribution, you can
install GConjugue from official repositories:

```
sudo apt-get install gconjugue
```

You can get information on how the application works at the menu item
*Help/Contents* (whose source code is in `src/callbacks.c`).

GConjugue is based on conjugue, a free software developed by
[Ricardo Ueda Karpischek](http://www.ime.usp.br/~ueda/br.ispell/conjugue.html).


## Compiling and installing

Two binaries are generated from the source code: `gconjugue` (GTK+
application) and `conjugar` (text only application). Most users will be
interested in `gconjugue`, but those wanting to use the output in other
applications, such as a web page, have to run `conjugar`.

In addition to a C compiler you will need the libraries and development files
for GTK+ to build `gconjugue`. On Debian or Debian based systems, like Ubuntu,
install the package *libgtk-3-dev* and its dependencies. On other systems the
package might be called *gtk3-devel*.
  
### Released versions


The *configure* script will warn you about missing dependencies. 
To compile GConjugue do:
  
```
./configure
make
sudo make install
```

### Development version

To build and install the development version, before the commands above, do:

```
./autogen.sh
```

## GTK+ GUI and TUI

If you do not want to build the GTK+ Graphical User Interface do:

```
./configure --enable-gtkgui=no
```

If you do not need the Text User Interface, do:

```
./configure --enable-tui=no
```

Note: Both applications are known to work in environments with UTF-8 character
encoding.

The file LeiaMe.md (in Portuguese) has additional information and some ideas
for future development.

## Old versions

   - [gconjugue-0.7.1.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KdloxWGRUbDgzXzA) (md5sum 6273dbc114888c64051975d32882a903)

   - [gconjugue-0.7.2.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KeXRLbVptejQ2LW8) (md5sum b21b99bb4d78348ae8443c3179e9e9b2)

   - [gconjugue-0.7.3.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KaDE1M2pxNHFiTTg) (md5sum 1d6a5f676511888b830c55dabf107dd4)

   - [gconjugue-0.7.4.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KaTlZVmJoZXpVLTA) (md5sum d318301a45e06f30dbbd990cbcecfb1d)

Even older versions were hosted at codigolivre.org.br (no longer online).
