#!/usr/bin/perl

use Finance::Quote;
use Data::Dumper;

$q = Finance::Quote->new;
$q->timeout(60);
#$conversion_rate = $q->currency("AUD","USD");
$q->set_currency("KRW");  # Return all info in Euros.
#$q->require_labels(qw/price date high low volume/);
$q->require_labels(qw/price name/);
$q->failover(1); # Set failover support (on by default).

@labels = qw/price net p_change name/;

#159000 1624000 1061325 8267437 801250 279000

%stocks = (
"000660.KS" => [0,0],
"030200.KS" => [30,1347000],
"035250.KS" => [10,159000],
"078520.KQ" => [70,1270500],
"088980.KS" => [1000,4863199], 
"067250.KS" => [0,0],
"069500.KS" => [0,0],
"091160.KS" => [0,0],
"102960.KS" => [0,0],
"000700.KS" => [0,0],
"095660.KQ" => [0,0],
"086790.KS" => [0,0],
"105560.KS" => [0,0],
"034220.KS" => [0,0],
"086790.KS" => [100,3338500],
);

$cash = "15404205";

%quotes  = $q->fetch("asia",keys %stocks);

my %result;
foreach (keys %stocks)
{
	$result{$_}{"hold"} = $stocks{$_}[0];
        $result{$_}{"invested"} = $stocks{$_}[1];
}

foreach (keys %quotes)
{
	$id = $n = undef;
	foreach $candi (keys %stocks)
	{
		$id = $candi if /^$candi/;
	}

	foreach $name (@labels)
	{
		$n = $name if /$name$/
	}

	$result{$id}{$n} = $quotes{$_} if $id and $n;
}

format STDOUT_TOP =
name                       price             holds             total
-------------------------------------------------------------------------------
.

format STDOUT =
@<<<<<<<<<<<<<<<<<<  @>>>>>>>(@<<<<<<<)    @<<<<<<<<  @>>>>>>>>>>>>>(@>>>>>%)
$r{"name"} $r{"price"} $r{"net"} $r{"hold"} $r{"price"}*$r{"hold"} $r{"invested"}?$r{"price"}*$r{"hold"}/$r{"invested"}*100-100:"---"
.

my $sum=0;

foreach (keys %result)
{
    %r = %{$result{$_}};
    if($r{"hold"} > 0)
    {
	$sum += $r{"price"} * $r{"hold"};
	write STDOUT;
    }
}


print "-------------------------------------------------------------------------------\n";

foreach (keys %result)
{
    %r = %{$result{$_}};
    if($r{"hold"} == 0)
    {
	write STDOUT;
    }
}

print "-------------------------------------------------------------------------------\n";

$sum += $cash;

print "Cash : $cash\n";
print "Total : $sum\n";

print "Sell Log\nKT 46250\nLGD 37650\nHANA 35950\n";

#print Dumper(%result);
