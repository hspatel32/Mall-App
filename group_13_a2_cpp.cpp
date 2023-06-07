/*
* Name:-   Harsh Shaileshkumar Patel
* ID:      144938206
* E-Mail:- hspatel32@myseneca.ca
* Name:-   Harsh Mittal
* ID:-     146122205
* E-Mail:- hmittal3@myseneca.ca
* Name:-   Dharm Hasmukhlal Pankhania
* ID:-     110362217
* E-Mail:- dhpankhania@myseneca.ca
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

//Global Variables:-

//Harsh Shaileshkumar
class Customer {
public:
	int customer_id;
	int order_number;
	string first_name;
	string last_name;
	string address;
};

//Dharam
class Orderdetails {
public:
	int order_num;
	string date;
	int store_id;
	int orderline;
	int qty;
};

//Harsh Mittal
class Employee {
public:
	int employee_id;
	int store_id;
	string employee_name;
	string employee_job;
	float salary;
};

//Function Declaration:-
//Harsh's function:-
void SPcustomerinfoINSERT(Connection* conn) {
	Customer customer;
	int err_code = 0;

	std::cout << "Customer ID: ";
	cin >> customer.customer_id;
	std::cout << "First Name: ";
	cin >> customer.first_name;
	std::cout << "Last Name: ";
	cin >> customer.last_name;
	std::cout << "Order Number: ";
	cin >> customer.order_number;
	std::cout << "Address: ";
	std::cin.ignore(); // ignore any leftover newline character
	std::getline(std::cin, customer.address);


	try {
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPcustomerinfoINSERT(:1, :2, :3, :4, :5,:6); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, customer.customer_id);
		stmt->setString(3, customer.first_name);
		stmt->setString(4, customer.last_name);
		stmt->setNumber(5, customer.order_number);
		stmt->setString(6, customer.address);

		stmt->executeUpdate();

		err_code = stmt->getInt(1);
		if (err_code > 0) {
			std::cout << "\nNew Customer Inserted.";
		}
		else {
			std::cout << "\nERROR: The Entered Customer id may already exists.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void SPcustomerinfoUPDATE(Connection* conn) {
	Customer customer;
	int err_code = 0;

	std::cout << "Customer ID: ";
	cin >> customer.customer_id;
	std::cout << "Enter New Address: ";
	std::cin.ignore(); // ignore any leftover newline character
	std::getline(std::cin, customer.address);

	try
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPcustomerinfoUPDATE(:1, :2,:3); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, customer.customer_id);
		stmt->setString(3, customer.address);

		stmt->executeUpdate();
		err_code = stmt->getInt(1);

		if (err_code == 1) {
			std::cout << "\nCustomer address updated successfully.\n\n";
		}
		else if (err_code == 0) {
			std::cout << "\nERROR: Customer with entered ID not found.\n\n";
		}
		else {
			std::cout << "\nERROR: The entered Customer ID may not exist.\n\n";
		}

		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}


void SPcustomerinfoDELETE(Connection* conn) {
	Customer customer;
	int err_code = 0;

	std::cout << "Customer ID: ";
	cin >> customer.customer_id;
	try {
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPcustomerinfoDELETE(:1, :2); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, customer.customer_id);

		stmt->executeUpdate();
		err_code = stmt->getInt(1);
		if (err_code == 1) {
			std::cout << "\nSUCCESS: Customer's record has been deleted.\n\n";
		}
		else if (err_code == 0) {
			std::cout << "\nERROR: Customer's record could not be deleted.\n\n";
		}
		else {
			std::cout << "\nERROR: Customer's record with ID " << customer.customer_id << " does not exist.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void spCustomerinfoSelect(Connection* conn) {
	int customer_id;
	int order_number;
	string first_name;
	string last_name;
	string address;

	std::cout << "Enter Customer ID: ";
	cin >> customer_id;

	try
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPcustomerinfoSELECT(:1, :2, :3, :4, :5, :6); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(int));
		stmt->setNumber(2, customer_id);
		stmt->registerOutParam(3, Type::OCCISTRING, sizeof(first_name));
		stmt->registerOutParam(4, Type::OCCISTRING, sizeof(last_name));
		stmt->registerOutParam(5, Type::OCCIINT, sizeof(order_number));
		stmt->registerOutParam(6, Type::OCCISTRING, sizeof(address));

		stmt->executeUpdate();
		int err_code = stmt->getInt(1);
		if (err_code == 1) {
			int order_number = stmt->getInt(5);
			string first_name = stmt->getString(3);
			string last_name = stmt->getString(4);
			string address = stmt->getString(6);

			std::cout << "****Customer Information****" << endl;
			std::cout << "\nCustomer ID: " << customer_id << endl;
			std::cout << "First Name: " << first_name << endl;
			std::cout << "Last Name: " << last_name << endl;
			std::cout << "Order Number: " << order_number << endl;
			std::cout << "Address: " << address << endl;
		}
		else {
			std::cout << "\nERROR: Customer record with ID " << customer_id << " does not exist.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void SPorderdetailsINSERT(Connection* conn) {
	Orderdetails order;
	int err_code = 0;

	std::cout << "Order Number: ";
	cin >> order.order_num;
	std::cout << "Order Date[DD-MMM-YY]: ";
	std::cin.ignore();
	std::getline(std::cin, order.date);
	std::cout << "Store ID: ";
	cin >> order.store_id;
	std::cout << "OrderLine Number: ";
	cin >> order.orderline;
	std::cout << "Quantity: ";
	cin >> order.qty;


	try {
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPorderdetailsINSERT(:1, :2, :3, :4, :5,:6); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setInt(2, order.order_num);
		stmt->setString(3, order.date);
		stmt->setInt(4, order.store_id);
		stmt->setInt(5, order.orderline);
		stmt->setInt(6, order.qty);

		stmt->executeUpdate();

		err_code = stmt->getInt(1);
		if (err_code > 0) {
			std::cout << "\nNew Order Record Added.";
		}
		else {
			std::cout << "ERROR: The Entered Ordered Number may already exists.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void SPorderdetailsUPDATE(Connection* conn) {
	Orderdetails order;
	int err_code = 0;

	std::cout << "Order Number: ";
	cin >> order.order_num;
	std::cout << "Enter Changed Quantity: ";
	cin >> order.qty;

	try
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPorderdetailsUPDATE(:1, :2,:3); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, order.order_num);
		stmt->setInt(3, order.qty);

		stmt->executeUpdate();
		err_code = stmt->getInt(1);

		if (err_code == 1) {
			std::cout << "\nOrdered Quantity updated successfully.\n\n";
		}
		else if (err_code == 0) {
			std::cout << "\nERROR: Order with entered Number not found.\n\n";
		}
		else {
			std::cout << "\nERROR: The entered Order Number may not exist.\n\n";
		}

		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}



void SPorderdetailsDELETE(Connection* conn) {
	Orderdetails order;
	int err_code = 0;

	std::cout << "Order Number: ";
	cin >> order.order_num;

	try {
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPorderdetailsDELETE(:1, :2); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, order.order_num);

		stmt->executeUpdate();
		err_code = stmt->getInt(1);
		if (err_code == 1) {
			std::cout << "\nSUCCESS: Order record with Number " << order.order_num << " has been deleted.\n\n";
		}
		else if (err_code == 0) {
			std::cout << "\nERROR: Order record could not be deleted.\n\n";
		}
		else {
			std::cout << "\nERROR: Order record with Number " << order.order_num << " does not exist.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void SPorderdetailsSELECT(Connection* conn) {
	int order_num;
	string date;
	int store_id;
	int orderline;
	int qty;

	std::cout << "Enter Order Number: ";
	cin >> order_num;

	try
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN SPorderdetailsSELECT(:1, :2, :3, :4, :5, :6); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(int));
		stmt->setNumber(2, order_num);
		stmt->registerOutParam(3, Type::OCCISTRING, sizeof(date));
		stmt->registerOutParam(4, Type::OCCIINT, sizeof(store_id));
		stmt->registerOutParam(5, Type::OCCIINT, sizeof(orderline));
		stmt->registerOutParam(6, Type::OCCIINT, sizeof(qty));

		stmt->executeUpdate();
		int err_code = stmt->getInt(1);
		if (err_code == 1) {
			string date = stmt->getString(3);
			int store_id = stmt->getInt(4);
			int orderline = stmt->getInt(5);
			int qty = stmt->getInt(6);

			std::cout << "Order Information" << endl;
			std::cout << "\nOrder Number: " << order_num << endl;
			std::cout << "Date: " << date << endl;
			std::cout << "Store ID: " << store_id << endl;
			std::cout << "Orderline Number: " << orderline << endl;
			std::cout << "Quantity: " << qty << endl;
		}
		else {
			std::cout << "\nERROR: Order record with ID " << order_num << " does not exist.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

// spEmployeeInsert
void spEmployeeInsert(Connection* conn) {
	Employee employee;
	int err_code = 0;

	std::cout << "Employee ID: ";
	cin >> employee.employee_id;
	std::cout << "store id: ";
	cin >> employee.store_id;
	std::cout << "employee name ";
	cin >> employee.employee_name;
	std::cout << "Salary: ";
	cin >> employee.salary;
	std::cout << "Employee job: ";
	cin >> employee.employee_job;

	try {
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spEmployeeInsert(:1, :2, :3, :4, :5,:6); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, employee.employee_id);
		stmt->setNumber(3, employee.store_id);
		stmt->setString(4, employee.employee_name);
		stmt->setNumber(5, employee.salary);
		stmt->setString(6, employee.employee_job);




		stmt->executeUpdate();
		err_code = stmt->getInt(1);
		if (err_code > 0) {
			std::cout << "\nNew Employee Inserted.";
		}
		else {
			std::cout << "ERROR: The Entered Employee id may already exists.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}


// spEmployeeUpdate
void spEmployeeUpdate(Connection* conn)
{
	Employee employee;
	int err_code = 0;
	std::cout << "Customer ID: ";
	cin >> employee.employee_id;
	std::cout << "Enter New Salary: ";
	std::cin.ignore(); // ignore any leftover newline character
	cin >> employee.salary;

	try
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spEmployeeUpdate(:1, :2,:3); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, employee.employee_id);
		stmt->setFloat(3, employee.salary);

		stmt->executeUpdate();
		err_code = stmt->getInt(1);

		if (err_code == 1) {
			std::cout << "\nEmployee Salary updated successfully.\n\n";
		}
		else if (err_code == 0) {
			std::cout << "\nERROR: Employee not found.\n\n";
		}
		else {
			std::cout << "\nERROR: The entered Employee id may not exist.\n\n";
		}

		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}


// spEmployeeDelete
void spEmployeeDelete(Connection* conn) {
	Employee employee;
	int err_code = 0;

	std::cout << "Employee Id: ";
	cin >> employee.employee_id;
	try {
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spEmployeeDelete(:1, :2); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(err_code));
		stmt->setNumber(2, employee.employee_id);

		stmt->executeUpdate();
		err_code = stmt->getInt(1);
		if (err_code == 1) {
			std::cout << "\nSUCCESS: Employee's record has been deleted.\n\n";
		}
		else if (err_code == 0) {
			std::cout << "\nERROR: Employee's record could not be deleted.\n\n";
		}
		else {
			std::cout << "\nERROR: Employee's record with ID " << employee.employee_id << " does not exist.\n\n";
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		std::cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}


//spEmployeeSelect
void spEmployeeSELECT(Connection* conn)
{
	int employee_id;
	int store_id;
	string employee_name;
	string employee_job;
	float salary;
	int err_code;

	cout << "Enter employee ID: ";
	cin >> employee_id;

	try
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("BEGIN spEmployeeSELECT(:1, :2, :3, :4, :5, :6, :7); END;");
		stmt->registerOutParam(1, Type::OCCIINT, sizeof(employee_id));
		stmt->setNumber(2, employee_id);
		stmt->registerOutParam(3, Type::OCCICHAR, sizeof(employee_name));
		stmt->registerOutParam(4, Type::OCCICHAR, sizeof(employee_job));
		stmt->registerOutParam(6, Type::OCCIFLOAT, sizeof(salary));
		stmt->registerOutParam(7, Type::OCCIINT, sizeof(err_code));

		stmt->executeUpdate();

		err_code = stmt->getInt(7);
		if (err_code == 1) {
			employee_id = stmt->getInt(1);
			store_id = stmt->getInt(2);
			employee_name = stmt->getString(3);
			employee_job = stmt->getString(4);
			salary = stmt->getFloat(6);

			cout << "\nEmployee ID: " << employee_id << endl;
			cout << "Store ID: " << store_id << endl;
			cout << "Employee Name: " << employee_name << endl;
			cout << "Employee Job: " << employee_job << endl;
			cout << "Salary: $" << salary << endl;
		}
		else {
			cout << "\nERROR: Employee record with ID " << employee_id << " does not exist.\n\n";
		}

		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp)
	{
		cerr << "Error: " << sqlExcp.getMessage() << endl;
	}
}

int main(void) {
	Environment* env = nullptr;
	Connection* conn = nullptr;

	string str;
	// Used Harsh Shaileshkumar's Login INFO
	string usr = "dbs311_231zbb35";
	string pass = "24499269";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";
	//// Used Dharam's Login INFO
	//string usr = "dbs311_231zbb33";
	//string pass = "31677148";
	//string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";
	////Used Harsh Mittal's Login INFO
	//string str;
	//string usr = "dbs311_231zbb30";
	//string pass = "62121529";
	//string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";
	try
	{
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		cout << "\nGroup Number:- 13\n\n" << endl;
		cout << "*** Mall Application ***\n\n" << endl;
		cout << "Harsh Shaileshkumar Patel(Student Number:- 144938206)\nDharm Hasmukhlal Pankhania(Student Number:- 110362217)\nHarsh Mittal(Student Number:- 146122205)" << endl;


		cout << "\n\n**********Menu**********\n\n" << endl;


		int opt = 0;
		do {
			cout << "\n\n0)Exit\n1)Add New Customer Record\n2)Update Customer Address\n3)Delete Customer Record\n4)Display Customer Details\n5)Add New Order Record\n6)Update Order Quantity\n7)Delete Order Record\n8)Display Order Details\n9) Insert an Employee\n10) Update an Employee\n11) Delete an Employee\n12) Display an Employee\n\n-> ";
			std::cin >> opt;
			if (opt < 0 || opt>12) {
				cout << "Invalid Input" << endl;
			}
			else {
				switch (opt) {
				case 0:
					cout << "Exited";
					env->terminateConnection(conn);
					Environment::terminateEnvironment(env);
					break;

				case 1:
					SPcustomerinfoINSERT(conn);
					break;

				case 2:
					SPcustomerinfoUPDATE(conn);
					break;

				case 3:
					SPcustomerinfoDELETE(conn);
					break;

				case 4:
					spCustomerinfoSelect(conn);
					break;

				case 5:
					SPorderdetailsINSERT(conn);
					break;

				case 6:
					SPorderdetailsUPDATE(conn);
					break;

				case 7:
					SPorderdetailsDELETE(conn);
					break;

				case 8:
					SPorderdetailsSELECT(conn);
					break;
				case 9:
					spEmployeeInsert(conn);
					break;

				case 10:
					spEmployeeUpdate(conn);
					break;

				case 11:
					spEmployeeDelete(conn);
					break;

				case 12:
					spEmployeeSELECT(conn);
					break;
				}
			}
		} while (opt != 0);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}




