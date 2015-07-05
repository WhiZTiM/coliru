<?php

function namedtuple($outtype, $intypes)
{
    $tn = array_map(function($value)
    {
        $tn = explode("-", $value);
        return array("type" => $tn[0], "name" => $tn[1]);
    }, explode(",", $intypes));
	
    $types_string = implode(array_map(function($v) { return $v["type"]; }, $tn), ",");
    $res = "struct $outtype : ";
    $res .= " std::tuple<$types_string> { \n";
    $index = 0;
    foreach($tn as $v)
    {
        $res .= "decltype(auto) $v[name] () { return std::get<$index>(*this); }\n";
        $res .= "decltype(auto) $v[name] () const { return std::get<$index>(*this); }\n";
		++$index;
    }
    $res .= "};";
    return $res;
}
?>

#include <iostream>
#include <tuple>

<?= namedtuple("person", "int - age, std::string - name, bool - is_available"); ?>



int main()
{
    person whoever;
    whoever.name() = "meh";
    whoever.is_available() = false;
    whoever.age() = 42;
    std::cout << std::get<0>(whoever) << " " << std::get<1>(whoever) << " " << std::get<2>(whoever);
}