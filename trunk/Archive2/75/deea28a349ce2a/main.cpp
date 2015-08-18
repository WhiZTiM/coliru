#include <iostream>
#include <pqxx/pqxx> /* Header for libpqxx library */

int insertintobidask(int argc, char *argv[])
{
 if (argc != 6)
 {
  std::cerr << "Give me a conninfo, ticker, datetime, bid, and ask. No more, no less." << std::endl;
  return 2;
 }

 try
 {  
  pqxx::connection conn(argv[1]);
  pqxx::work txn(conn);
 /* Use quote() to escape and quote a value safely for use in a query.  Avoid bugs and security holes when strings contain backslashes, quotes, or other "weird" characters. */
 txn.exec("INSERT INTO fx.bidask VALUES (" + txn.quote(argv[2]) + ", to_timestamp(" + txn.quote(argv[3]) + ", 'YYYYMMDD HH24MISSMS'), " + txn.quote(argv[4]) + ", " + txn.quote(argv[5]) + ")");
  /* Commit. If we neglect to do this (e.g. because the program crashed) then our changes will be rolled back. */
  txn.commit();
 }
 catch (const std::exception &e)
 {
  /* Our transaction's destructor has already been called, so our change is implicitly rolled back before we get here. */
  std::cerr << e.what() << std::endl;
  return 1;
 }
}