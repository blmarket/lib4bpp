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

@labels = qw/price name/;

%stocks = ("069500.KS" => 230, "088980.KS" => 1200, "067250.KS" => 120, "000700.KS" => 50);
$cash = "531546";

%quotes  = $q->fetch("asia",keys %stocks);

my %result;
foreach (keys %stocks)
{
	$result{$_}{"hold"} = $stocks{$_};
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
name                 price       holds      total
--------------------------------------------------------
.

format STDOUT =
@<<<<<<<<<<<<<<<<<<  @<<<<<<<    @<<<<<<<<  @<<<<<<<<<<<<<
$r{"name"} $r{"price"} $r{"hold"} $r{"price"}*$r{"hold"}
.

my $sum=0;

foreach (keys %result)
{
	%r = %{$result{$_}};
	$sum += $r{"price"} * $r{"hold"};
	write STDOUT;
#	print $result{$_}{"name"}."\t\t".$result{$_}{"price"}."\t\t".$result{$_}{"hold"}."\n";
}

print "--------------------------------------------------------\n";

$sum += $cash;

print "Cash : $cash\n";
print "Total : $sum\n";

#print Dumper(%result);