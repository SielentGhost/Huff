void decode(string Encoded_file, string Decoded_file) {
	int xx, yy;
	char zz;
	map<char, int> M;
	list<Node*> t;
	ifstream in(Encoded_file, ios::binary);
	ofstream out;
	out.open(Decoded_file);
	in.read((char*)&xx, sizeof(xx));
	xx -= 32;
	while (xx > 0) {
		in.read((char*)&zz, sizeof(zz));
		in.read((char*)&yy, sizeof(yy));
		xx -= 40;
		M[zz] = yy;
	}
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
	Node *rootout = t.front();
	BuildTable(rootout);
	char buf1;
	vector<bool> buf2;
	while (in.read((char*)&buf1, sizeof(buf1))) {
		for (int i = 7; i >= 0; i--) {
			buf2.push_back((buf1 >> i) & 1);
			for (int i = 0; i < 256; i++) {
				if (M[char(i)] > 0) {
					if (table[char(i)] == buf2) {
						out << char(i);
						buf2.clear();
					}
				}
			}
		}
	}
	in.close();
	out.close();
	return;
}
