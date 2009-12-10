#!/usr/bin/perl

use Finance::Quote;
use Data::Dumper;

$q = Finance::Quote->new;

$q->timeout(60);

#$conversion_rate = $q->currency("AUD","USD");
$q->set_currency("KRW");  # Return all info in Euros.

#$q->require_labels(qw/price date high low volume/);
$q->require_labels(qw/price/);

$q->failover(1); # Set failover support (on by default).

%stocks = { "069500.KS" => 230, "088980.KS" => 1100, "067250.KS" => 10, "000770.KS" => 10 };

@array = keys %stocks;
print Dumper(@array);


%quotes  = $q->fetch("asia","069500.KS", "088980.KS");

foreach (keys %quotes)
{
	print "$_ => $quotes{$_}\n" if /price$/;
}

print Dumper(%quotes);
