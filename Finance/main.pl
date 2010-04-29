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
"035250.KS" => 10, 
"067250.KS" => 100,
"069500.KS" => 200,
"088980.KS" => 1000, 
"091160.KS" => 0,
"102960.KS" => 300,
"000660.KS" => 0,
"000700.KS" => 0,
"095660.KQ" => 0,
);

%invested = (
"035250.KS" => 159000,
"067250.KS" => 1378219,
"069500.KS" => 4618000,
"088980.KS" => 4863199,
"091160.KS" => 0,
"102960.KS" => 5004185,
"095660.KQ" => 0,
);
$cash = "3633510";

%quotes  = $q->fetch("asia",keys %stocks);

my %result;
foreach (keys %stocks)
{
	$result{$_}{"hold"} = $stocks{$_};
        $result{$_}{"invested"} = $invested{$_};
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

#print Dumper(%result);
