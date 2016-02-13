#include "stdafx.h"

#include "csv_io.h"
using namespace std;

template <typename T>
vector<int> get_order(const vector<T>& v) {
	// Initialize original index locations
	vector<int> idx(v.size());
	for (size_t i = 0; i < idx.size(); ++i) idx[i] = i;
	// Sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(), [&v](int i1, int i2) {return v[i1] > v[i2];});
	return idx;
}

string merge_cells(const vector<string>& cells) {
	int i;
	string result = "";
	for (i = 0; i < cells.size() - 1; ++i) {
		result += cells[i] + ", ";
	}
	result += cells[i];
	return result;
}

vector<string> split_line(const std::string& line)
{
	stringstream lineStream(line);
	string cell;
	vector<string> result;
	while (getline(lineStream, cell, ','))
	{
		result.push_back(cell);
	}
	return result;
}

csv_io::csv_io(void) {
	fname = "";
	L = 0;
	M = 0;
}

csv_io::~csv_io(void) {
	if (ifile.is_open()) {
		ifile.close();
	}
	if (ofile.is_open()) {
		ofile.close();
	}
}

bool csv_io::getproblem(void) {
	vector<string> cells;
	bool stat = false;
	string line;
	try {
		while (!ifile.eof()) {
			getline(ifile, line);
			if (line.find("Length of stock material") != string::npos) {
				stat = true;
				cells = split_line(line);
				L = stoi(cells[1]);
				break;
			}
		}
		if (stat) {
			getline(ifile, line); // Ignore this line of text
			M = 0;
			// Start reading in orders
			while (!ifile.eof()) {
				getline(ifile, line);
				// Check for terminating character
				if (line.find("-") != string::npos) {
					break;
				}
				else {
					if (line == "") break;
					cells = split_line(line);
					Lv.push_back(stoi(cells[0]));
					qv.push_back(stoi(cells[1]));
					++M;
				}
			}
		}
	}
	catch (const std::invalid_argument& ia) {
		cerr << "Unable to convert " << ia.what() << " into a numerical value." << endl;
		cout << "Type something and hit ENTER to exit... ";
		cin >> line;
		exit(EXIT_FAILURE);
	}
	return stat;
}

void csv_io::reset(void) {
	L = 0;
	M = 0;
	Lv.clear();
	qv.clear();
}

void csv_io::setfilename(const string& root) {
	string temp;
	fname = root;
	temp = fname + ".csv";
	ifile.open(temp, ios::in);
	if (!ifile.is_open()) {
		cerr << "Unable to open input file " << temp << ". Aborting..." << endl;
		cout << "Type something and hit ENTER to exit... ";
		cin >> temp;
		exit(EXIT_FAILURE);
	}
	temp = fname + "-solution.csv";
	ofile.open(temp, ios::out);
	if (!ofile.is_open()) {
		cerr << "Unable to open output file " << temp << ". Aborting..." << endl;
		cout << "Type something and hit ENTER to exit... ";
		cin >> temp;
		exit(EXIT_FAILURE);
	}
}

void csv_io::sort(void) {
	int i;
	vector<int> ordering, temp;
	// Compute ordering based off Lv (in descending order)
	ordering = get_order(Lv);
	// Reorder Lv and qv accordingly
	temp.assign(M, 0);
	for (i = 0; i < M; ++i) {
		temp[i] = Lv[ordering[i]];
	}
	Lv = temp;
	for (i = 0; i < M; ++i) {
		temp[i] = qv[ordering[i]];
	}
	qv = temp;
}

void csv_io::writesolution(const vector<int>& xv, const vector<pttn>& S) {
	// Precompute information first
	int i, j, xsum, xct, xoverallsum;
	double pct;
	vector<int> qvs;
	xoverallsum = 0;
	xsum = 0;
	xct = 0;
	qvs.assign(M, 0);
	for (i = 0; i < xv.size(); ++i) {
		if (xv[i] > 0) {
			xoverallsum += xv[i] * S[i].c;
			xsum += xv[i];
			++xct;
			for (j = 0; j < M; ++j) {
				qvs[j] += xv[i] * S[i].a[j];
			}
		}
	}
	pct = ((double)xoverallsum) / (xsum * L) * 100.0;
	// Now start formatting and writing
	vector<string> cells;
	string line;
	// First line: Length of stock material
	line = "Length of stock material, " + to_string(L);
	ofile << line << endl;
	// Second line: Number of stock material used
	line = "Number of stock material used, " + to_string(xsum);
	ofile << line << endl;
	// Third line: Total percentage waste
	line = "Total percentage waste, " + to_string(pct) + "%";
	ofile << line << endl;
	// Fourth line: Number of patterns used
	line = "Number of patterns used, " + to_string(xct);
	ofile << line << endl;
	// Blank line
	ofile << "," << endl;
	// Table of pattern & order information
	cells.assign(M + 1, "");
	cells[0] = "Order width";
	for (j = 0; j < M; ++j) {
		cells[j + 1] = to_string(Lv[j]);
	}
	line = merge_cells(cells);
	ofile << line << endl << "Quantity of pattern" << endl;
	for (i = 0; i < xv.size(); ++i) {
		if (xv[i] > 0) {
			cells.assign(M + 1, "");
			cells[0] = to_string(xv[i]);
			for (j = 0; j < M; ++j) {
				cells[j + 1] = to_string(S[i].a[j]);
			}
			line = merge_cells(cells);
			ofile << line << endl;
		}
	}
	cells.assign(M + 1, "");
	cells[0] = "Order quantity supplied";
	for (j = 0; j < M; ++j) {
		cells[j + 1] = to_string(qvs[j]);
	}
	line = merge_cells(cells);
	ofile << line << endl;
	cells.assign(M + 1, "");
	cells[0] = "Order quantity required";
	for (j = 0; j < M; ++j) {
		cells[j + 1] = to_string(qv[j]);
	}
	line = merge_cells(cells);
	ofile << line << endl;
	// Blank line
	ofile << "," << endl;
	// Terminating line
	cells.assign(M + 1, "-");
	line = merge_cells(cells);
	ofile << line << endl;
	// Blank line
	ofile << "," << endl;
}