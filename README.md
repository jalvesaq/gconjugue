# GConjugue

The application conjugates Portuguese verbs as spoken in Brazil. It is based
on conjugue, a free software developed by
[Ricardo Ueda Karpischek](http://www.ime.usp.br/~ueda/br.ispell/conjugue.html).

![Screenshot](http://www.lepem.ufc.br/jaa/gconjugue/gconjugue-en.png "Screenshot")

If you are using Debian, Ubuntu or another Debian based distribution, you can
install GConjugue from official repositories:

```
sudo apt-get install gconjugue
```

## Compiling and installing

In addition to a C compiler you will need the libraries and development files
for GTK+. On Debian or Debian based systems, like Ubuntu, install the package
*libgtk-3-dev* and its dependencies. On other systems the package might be
called *gtk3-devel*.
  
### Released versions


The *configure* script will warn you about missing dependencies. 
To compile GConjugue do:
  
```
./configure
make
sudo make install
```

### Development version

To build and install the development version, do:

```
./autogen.sh
make
sudo make install
```

The file LeiaMe.md (in Portuguese) has additional information and some ideas
for future development.

## Old versions

   - [gconjugue-0.7.1.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KdloxWGRUbDgzXzA) (md5sum 6273dbc114888c64051975d32882a903)

   - [gconjugue-0.7.2.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KeXRLbVptejQ2LW8) (md5sum b21b99bb4d78348ae8443c3179e9e9b2)

   - [gconjugue-0.7.3.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KaDE1M2pxNHFiTTg) (md5sum 1d6a5f676511888b830c55dabf107dd4)

   - [gconjugue-0.7.4.tar.gz](https://drive.google.com/uc?export=download&id=0ByMBQcSs9G7KaTlZVmJoZXpVLTA) (md5sum d318301a45e06f30dbbd990cbcecfb1d)

Even older versions were hosted at codigolivre.org.br (no longer online).

