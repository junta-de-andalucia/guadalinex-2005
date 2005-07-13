#!/bin/sh

DIR=$1
OUT=$2
WHICH=$3

SCRIPTDIR=/srv/cdimage.no-name-yet.com/britney/update_out

if [ "$DIR" = "" ]; then DIR=~/testing/out; fi
if [ "$OUT" = "" ]; then OUT=~/public_html/testing_probs.html; fi
if [ "$WHICH" = "" ]; then WHICH=testing; fi

(
  echo "<html><head><title>Problems with $WHICH</title></head><body>"
  echo "<p>Generated:"
  TZ=UTC date
  echo "<hr>"
  echo "<p>First, uninstallable packages:</p>"
  echo "<ul>"
  export cnt=0
  last=""
  (
    $SCRIPTDIR/check_out.py $DIR | sort | grep uninstallable
  ) | sed 's/(/ /;s/)//' | awk '
      BEGIN { last=""; cnt=0 }
      {
        src = $1; ver = $2; pkg = $3; arch = $4;
        if (last != src) {
          if (last != "") {
            print "</ul>";
          }
          print "<li>Binaries from " src " " ver " cannot be installed:";
          print "<ul>";
        }
        print "    <li>" pkg "(" arch ")";
        cnt++;
        archcnt[arch]++;
        last=src;
      }
      END { 
        if (last != "") print "</ul>";
        print "</ul>"
        print "<p>Totals by arch:"
        print "<ul>"
        for (i in archcnt) { print "<li>" i ":" archcnt[i]; }
        print "</ul>"
        print "<p align=right>(there were " cnt " all up)</p>"
      }'


  if [ -e $DIR/Bugs ]; then
    echo "<hr>"
    echo "<p>Next the number of RC bugs that still seem to apply:</p>"
    echo "<ul>"
    cnt=0
    cat $DIR/Bugs | grep "^[^ ][^ ]* [0-9][0-9]*$" | (
      while read pkg bugs; do
        echo "<li><a href=\"update_excuses.html.gz#$pkg\">$pkg</a> --- <a href=\"http://bugs.debian.org/$pkg\">$bugs</a>"
        cnt=$[$cnt + $bugs]
      done
      echo "</ul>"
      echo "<p align=right>(there were $cnt all up)</p>"
    )
  fi
  echo "</body></html>"
) > "$OUT"

chmod 664  "$OUT"
