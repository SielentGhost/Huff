void encode(string Source, string Encoded_file) {
	map<char, int> M;
	list<Node*> t;
	int amount = 0, final_amount = 0;
	int hat_info = 0;
	char d;
	ifstream fin1, fin2;
	fin1.open(Source);
	if (!fin1.is_open()) {
		cout << "Error!" << endl;
	}
	else {
		cout << "File is opened!" << endl;
		while (fin1.get(d)) {
			M[d]++;
			amount++;
		}
	}
	cout << endl;
	fin1.close();
	for (map<char, int>::iterator itr = M.begin(); itr != M.end(); itr++) {
		Node *p = new Node;
		p->c = itr->first;
		p->a = itr->second;
		t.push_back(p);
	}
	while (t.size() != 1) {
		t.sort(MyCompare());
		Node *L = t.front();
		t.pop_front();
		Node *R = t.front();
		t.pop_front();
		Node *P = new Node(L, R);
		t.push_back(P);
	}
	Node *root = t.front();
	BuildTable(root);
	for (map<char, int>::iterator im = M.begin(); im != M.end(); im++) {
		if (im->second != 0) {
			char c = im->first;
			vector<bool> x = table[c];
			hat_info += 40;
			final_amount += (x.size()*(im->second));
		}
	}
	hat_info += 32;
	cout << "Compression ratio: " << float(final_amount+hat_info) / float(amount * 8) << endl;
	cout << "Are you going to continue?(Y or N)" << endl;
	char answer;
	cin >> answer;
	if (answer == 'N') return;
	ofstream out(Encoded_file, ios::binary);
	fin2.open(Source);
	unsigned char buf, f = 0;
	int j = 0, ex = 7;
	if (!fin2.is_open()) {
		cout << "Error!" << endl;
	}
	else {
		cout << "File is opened!" << endl;
		out.write((char*)(&hat_info), sizeof(hat_info));
		for (int i = 0; i < 256; i++) {
			if (M[char(i)] > 0) {
				d = char(i);
				out.write((char*)(&d), sizeof(d));
				out.write((char*)(&M[char(i)]), sizeof(M[char(i)]));
			}
		}
		while (fin2.get(d)) {
			vector<bool> x = table[d];
			for (int i = 0; i < x.size(); i++) {
				ex = 7 - j % 8;
				buf = x[i] << (ex);
				f |= buf;
				if (j % 8 == 7) {
					out.write((char*)(&f), sizeof(f));
					f = 0;
				}
				j++;
			}
		}
	}
	fin2.close();
	out.close();
	M.clear();
	t.clear();
	return;
}

