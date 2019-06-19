#!/usr/bin/perl
#
# Author: Akira Funahashi <funa_at_bio.keio.ac.jp>
#
# Usage: foreach i ({00001..00980}); echo -n "$i: "; /usr/bin/grep -i -B 1 testtags testsuite/cases/semantic/$i/$i-model.m; end | perl parseModel.pl
# Usage: for i in `./batchTestPrintFailed.sh 1-100`; do echo -n "$i: "; /usr/bin/grep -i -B 1 testtags testsuite/cases/semantic/$i/$i-model.m; done | perl parseModel.pl
#
# Last modified: Thu, 20 Jun 2019 02:42:50 +0900
#

use strict;
use warnings;

open(OUT, ">table.html") || die;

print OUT << "_EOH_";
<html>
<head>
  <link rel="stylesheet" href="mytable.css" type="text/css" media="screen, projection, tv, print" />
</head>
<body><center>
<table id="rounded-corner"><caption>SBML test cases 2.0.2</caption>
<thead>
  <tr>
    <th scope="col" class="rounded-company">Model</th>
    <th scope="col">Component1</th>
    <th scope="col">Component2</th>
    <th scope="col">Component3</th>
    <th scope="col">Component4</th>
    <th scope="col">Component5</th>
    <th scope="col">Component6</th>
    <th scope="col">Component7</th>
    <th scope="col">Component8</th>
    <th scope="col">Component9</th>
    <th scope="col">Component10</th>
    <th scope="col">Component11</th>
    <th scope="col">Component12</th>
    <th scope="col" class="rounded-q9">Component13</th>
  </tr>
</thead>
<tfoot>
  <tr>
    <td colspan="13" class="rounded-foot-left"><em>This table is generated by <a href="./parseModel.pl">parseModel.pl</a></em></td>
    <td class="rounded-foot-right"></td>
  </tr>
</tfoot>
<tbody>
_EOH_

my $maxlength = 0;
my $tmparraylength = 0;

while(<>) {
  chomp;
  if ($_ =~ /componentTags/) {
    # 00001: componentTags: Compartment, Species, Reaction, Parameter
    my ($id, $tag, $content) = split(/:/);
    my @strarray = split(/,/, $content);
    print OUT "  <tr>\n";
    print OUT "    <td>$id</td>\n";
    $tmparraylength = @strarray;
    foreach my $elem (@strarray) {
      $elem = ltrim(rtrim($elem));
      print OUT "    <td>$elem</td>\n";
    }
    $tmparraylength = @strarray;
  } else {
    # testTags:      Amount, NonUnityStoichiometry
    my ($tag, $content) = split(/:/);
    my @strarray = split(/,/, $content);
    foreach my $elem (@strarray) {
      $elem = ltrim(rtrim($elem));
      print OUT "    <td>$elem</td>\n";
    }
    my $arraylength = @strarray;
    for (my $i = 0; $i < 13 - $arraylength - $tmparraylength; $i++) {
      print OUT "    <td> </td>\n";
    }
    $tmparraylength = $tmparraylength + $arraylength;
    if ($tmparraylength > $maxlength) {
      $maxlength = $tmparraylength;
    }
    print OUT "  </tr>\n";
  }
}
print OUT "</tbody>\n</table>\n</center></body>\n</html>\n";

sub ltrim {
  my $val = shift;
  $val =~ s/^\s*//;
  return $val;
}

sub rtrim {
  my $val = shift;
  $val =~ s/\s*$//;
  return $val;
}
