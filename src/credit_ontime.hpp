#ifndef CREDIT_ONTIME_HPP
#define	CREDIT_ONTIME_HPP
#include "include.hpp"
#include "mysql/mysql_api.hpp"

//#define DEBUG
class credit_ontime
{
public:
	credit_ontime()
	{
		m_conn=boost::shared_ptr<MySql>(new MySql(get_config->m_ip.c_str(), get_config->m_username.c_str(), get_config->m_password.c_str(), get_config->m_database.c_str(), get_config->m_port));
		
		m_today_string=to_iso_extended_string(boost::gregorian::day_clock::local_day());
	}
	void start_update()
	{
		try
		{
			typedef tuple<unique_ptr<string>, unique_ptr<double> ,unique_ptr<string>> credit_tuple;
			
			//typedef tuple<string,double> credit_tuple;
			vector<credit_tuple> credits;
			string query_sql = "SELECT customer_credit_flow_id,balance,customer_master_id FROM " + get_config->m_database + "." + get_config->m_table + " where expire_date='" + m_today_string + "' and balance>0 and dr=0 and transaction_type=0";
			cout << query_sql << endl;
			m_conn->runQuery(&credits, query_sql.c_str());

			BOOST_LOG_SEV(slg, boost_log->get_log_level()) << query_sql;
			boost_log->get_initsink()->flush();
			/********************************/
			cout.setf(ios::showpoint); cout.setf(ios::fixed); cout.precision(8);
			/********************************/
			if(credits.empty())
			{
				BOOST_LOG_SEV(slg, boost_log->get_log_level()) << "nothing need to update";
				boost_log->get_initsink()->flush();
				cout<<"nothing need to update"<<endl;
			}
			for (const auto& item : credits)
			{
				cout << item << endl;

				string update_sql = "update " + get_config->m_database + "." + get_config->m_table + " set balance=0 where customer_credit_flow_id='" + *(std::get<0>(item))+"'";
				cout << update_sql << endl;
				string update_sql2;
				try
				{
					m_conn->runCommand(update_sql.c_str());
					//¸üÐÂÁíÒ»¸ö±í
					update_sql2 = "update " + get_config->m_database + "." + get_config->m_table2 + " set credit_balance=0 where customer_master_id='" + *(std::get<2>(item))+"'";
					cout << update_sql2 << endl;
					m_conn->runCommand(update_sql2.c_str());
					
					BOOST_LOG_SEV(slg, boost_log->get_log_level()) << update_sql;
					BOOST_LOG_SEV(slg, boost_log->get_log_level()) << update_sql2;
					boost_log->get_initsink()->flush();
				}
				catch (const MySqlException& e)
				{
					BOOST_LOG_SEV(slg, severity_level::error) << "(1)" << update_sql << "(2)" << update_sql2 << "(exception:)" << e.what();
					boost_log->get_initsink()->flush();
				}
				

				
			}

			credits.clear();
			}
		catch (const MySqlException& e)
		{
			BOOST_LOG_SEV(slg, severity_level::error) <<"(exception:)" << e.what();
			boost_log->get_initsink()->flush();
		}
	}
private:
	boost::shared_ptr<MySql> m_conn;
	string m_today_string;
};
#endif

