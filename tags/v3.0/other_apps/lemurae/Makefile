# This makefile is autogenerated by MonoDevelop
# Do not modify this file

SOURCES = \
./Main.cs \
./AssemblyInfo.cs

RESOURCES = \
./dicrae.glade \
./logo.png

RESOURCES_BUILD = $(foreach res,$(RESOURCES), $(addprefix -resource:,$(res)),$(notdir $(res)))

PKG_REFERENCES = \
gtk-sharp \
glade-sharp \
gecko-sharp \
gnome-sharp

PKG_REFERENCES_BUILD = $(addprefix -pkg:, $(PKG_REFERENCES))

PKG_REFERENCES_CHECK = $(addsuffix .pkgcheck, $(PKG_REFERENCES))

MCS_OPTIONS = 

all: lemurae.exe

lemurae.exe: $(SOURCES) $(RESOURCES)
	mcs $(MCS_OPTIONS) -target:exe -out:"lemurae.exe" $(RESOURCES_BUILD) $(PKG_REFERENCES_BUILD) $(SOURCES) \
	&& cp "lemurae.exe" ./build/bin/.

clean:
	rm -f lemurae.exe

depcheck: PKG_depcheck 

PKG_depcheck: $(PKG_REFERENCES_CHECK)

%.pkgcheck:
	@echo -n Checking for package $(subst .pkgcheck,,$@)...
	@if pkg-config --libs $(subst .pkgcheck,,$@) &> /dev/null; then \
		echo yes; \
	else \
		echo no; \
		exit 1; \
	fi

install:
	cp lemurae.exe /usr/bin/dicrae

uninstall:
	rm /usr/bin/dicrae

depend:
	apt-get install mono libgtk2.0-cil libgecko-cil


