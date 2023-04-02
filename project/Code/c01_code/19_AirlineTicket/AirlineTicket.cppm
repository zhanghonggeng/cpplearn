// export module 声明正在写模块 airline_ticket
export module airline_ticket;

import <string>;
// export class 显式导出希望模块使用者可用的类型
export class AirlineTicket
{
public:
	//AirlineTicket();
	//~AirlineTicket();

	double calculatePriceInDollars();
	
	std::string getPassengerName();
	void setPassengerName(std::string name);

	int getNumberOfMiles();
	void setNumberOfMiles(int miles);
	
	bool getHasEliteSuperRewardsStatus();
	void setHasEliteSuperRewardsStatus(bool status);

private:
	//std::string m_passengerName;
	//int m_numberOfMiles;
	//bool m_hasEliteSuperRewardsStatus;
	std::string m_passengerName{ "Unknown Passenger" };
	int m_numberOfMiles{ 0 };
	bool m_hasEliteSuperRewardsStatus{ false };
};
