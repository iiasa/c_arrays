#!/usr/bin/perl -w

##########################################################################################################
#                                                                                                        #
#  Source code generator for high performance multidimensional arrays (for C++) written in Perl.       #
#                                                                                                        #
#  The 3-Clause BSD License:                                                                             #
#                                                                                                        #
#  Copyright 2017 Nikolay Khabarov, International Institute for Applied Systems Analysis (IIASA).        #
#  Redistribution and use in source and binary forms, with or without modification, are permitted        #
#  provided that the following conditions are met:                                                       #
#                                                                                                        #
#  1. Redistributions of source code must retain the above copyright notice, this list of conditions     #
#     and the following disclaimer.                                                                      #
#                                                                                                        #
#  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions  #
#     and the following disclaimer in the documentation and/or other materials provided with the         #
#     distribution.                                                                                      #
#                                                                                                        #
#  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse  #
#     or promote products derived from this software without specific prior written permission.          #
#                                                                                                        #
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR        #
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND      #
#  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR            #
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL     #
#  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     #
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER    #
#  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT     #
#  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                       #
#                                                                                                        #
##########################################################################################################

##########################################################################################################
# Acknowledgement:                                                                                       #
# This work is supported by the Synergy Grant 610028 IMBALANCE-P: Effects of phosphorus limitations      #
# on Life, Earth system and Society (Horizon 2020 European Union Funding for Research and Innovation).   #
##########################################################################################################

use strict;

### Settings
my $maxdim = 5;
my $fname_in = "mdarray_template.hpp"; # this script needs the template file mdarray_template.hpp for input
my $dir_out = "src-generated/nik-mdarray-hpp";
#########################################

### Global variables
my $dim; 
my $template; 
#########################################

### Main program
print "Source code generator for high performance multidimensional arrays. (c) 2012-2017 Nikolay Khabarov, IIASA.\n";
print "Generating source code for arrays up to dimension $maxdim.\n";

undef $/; # no record separator to read entire file
open(INFILE, "< $fname_in") or die "Error: cannot open input file $fname_in";
my $templatesource = <INFILE>;

for ($dim = 1; $dim <= $maxdim; $dim++) {
	my $fname_out = "$dir_out\\nik-mdarray${dim}.hpp";	
	open(OUTFILE, "> $fname_out") or die "Error: cannot open output file $fname_out";	
	$template = $templatesource;
	filltemplate();
	print OUTFILE $template;
	close(OUTFILE);
}	
### Just copy the abstract base class, no need to modify its tmplate
`cp mdarrayX_template.hpp $dir_out/nik-mdarrayX.hpp`;
print "Done.";
#########################################

### Subroutine that does the replacements
sub filltemplate {	
	my $autogenerated_notice = "";	## !!autogenerated_notice!!	= // The code below was automatically generated out of a template.
	my $mdim = "";					## !!mdim!! = 3;
	my $assertcond = "";			## !!assertcond!! = (i0>=0) || (i1>=0) || (i2>=0) || (i0<dim0) || (i1<dim1) || (i2<dim2)
	my $dimargs = "";				## !!dimargs!! = size_t d0, size_t d1, size_t d2
	my $dimargsmul = "";			## !!dimargsmul!! = d0*d1*d2
	my $dimargsmuldouble = "";		## !!dimargsmul!! = ((double)d0)*((double)d1)*((double)d2)
	my $dimargslist = "";			## !!dimargslist!! = d0, d1, d2
	my $idxargs = "";				## !!idxargs!! = size_t i0, size_t i1, size_t i2
	my $dimlist = "";				## !!dimlist!! = dim0, dim1, dim2
	my $dimmul = "";				## !!dimmul!! = dim0*dim1*dim2
	my $diminit = "";				## !!diminit!! = dim0 = d0; dim1 = d1; dim2 = d2;
	my $indexing = "";				## !!indexing!! = i0*dim1*dim2 + i1*dim2 + i2
	my $dimlencases = "";			## !!dimlencases!! = case 0: return dim0; ... case 2: return dim2;   	
	
	$autogenerated_notice = "// The code below was automatically generated out of a template.";
	$mdim = $dim;
	for (my $i = 0; $i < $dim; $i++) {
		$assertcond .= "(i$i>=0) && (i$i<dim$i)"; $assertcond .= " && " if ($i < $dim - 1); 
		$dimargs .= "size_t d$i"; $dimargs .= ", " if ($i < $dim - 1);
		$dimargsmul .= "d$i"; $dimargsmul .= "*" if ($i < $dim - 1);
		$dimargsmuldouble .= "((double)d$i)"; $dimargsmuldouble .= "*" if ($i < $dim - 1);
		$dimargslist .= "d$i"; $dimargslist .= ", " if ($i < $dim - 1);
		$idxargs .= "size_t i$i"; $idxargs .= ", " if ($i < $dim - 1);
		$dimlist .= "dim$i"; $dimlist .= ", " if ($i < $dim - 1);
		$dimmul .= "dim$i"; $dimmul .= "*" if ($i < $dim - 1);
		$diminit .= "dim$i = d$i;"; $diminit .= " " if ($i < $dim - 1);
		$indexing .= "i$i";
		for (my $j = $i+1; $j < $dim; $j++) { $indexing .= "*dim$j"; }
		$indexing .= " + " if ($i < $dim - 1);
		$dimlencases .= "case $i: return dim$i;"; $dimlencases .= "\n\t\t" if ($i < $dim - 1);
	}
	
	$template =~ s/!!autogenerated_notice!!/$autogenerated_notice/g;
	$template =~ s/!!mdim!!/$mdim/g;  
	$template =~ s/!!assertcond!!/$assertcond/g;
	$template =~ s/!!dimargs!!/$dimargs/g;
	$template =~ s/!!dimargsmul!!/$dimargsmul/g;
	$template =~ s/!!dimargsmuldouble!!/$dimargsmuldouble/g;
	$template =~ s/!!dimargslist!!/$dimargslist/g;
	$template =~ s/!!idxargs!!/$idxargs/g;
	$template =~ s/!!dimlist!!/$dimlist/g;
	$template =~ s/!!dimmul!!/$dimmul/g;
	$template =~ s/!!diminit!!/$diminit/g;	
	$template =~ s/!!indexing!!/$indexing/g;		
	$template =~ s/!!dimlencases!!/$dimlencases/g;	
}
#########################################
