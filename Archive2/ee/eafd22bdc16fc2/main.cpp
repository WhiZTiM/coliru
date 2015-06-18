#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class rule
{
    string _identifier;
	vector<vector<rule*>> productions;
public:
	bool initial;
	rule(const bool init, const string& str) : initial(init), _identifier(str) {}

	typedef vector<vector<rule*>>::iterator iterator;
	typedef vector<vector<rule*>>::const_iterator const_iterator;
	iterator begin(){return productions.begin();}
	iterator end(){return productions.end();}
	size_t size(){return productions.size();}
	bool empty(){return productions.empty();}
	bool is_terminal(){return productions.empty();}
	vector<rule*>& operator[](int i){return productions[i];}

	string identifier()
	{
		return _identifier;
	}

	void print(const bool descend = true)
	{
		if (_identifier == "ɛ")
			cout << _identifier;
		else if (productions.empty())
			cout << "'" << _identifier << "'";
		else if (!descend)
			cout << "{" << _identifier << "}";
		else
		{
			cout << _identifier << " →";
			for (auto it = productions.begin();;)
			{
				for (auto& jt : *it)
				{
					cout << " ";
					jt->print(false);
				}
				if (++it == productions.end())
					break;
				cout << " |";
			}
		}
	}

	void add_production(vector<rule*>& vec, iterator it)
	{
		productions.insert(it, vec);
	}
	void add_production(vector<rule*>& vec)
	{
		productions.insert(productions.end(), vec);
	}
	void add_production(vector<rule*>&& vec)
	{
		productions.insert(productions.end(), vec);
	}
	void remove_production(iterator it)
	{
		productions.erase(it);
	}
};

class grammar
{
	rule *eps;
	unordered_map<string, rule*> rules;
	rule& new_rule()
	{
		static int n = 0;
		string ident = "_prod" + to_string(++n);
		rule *r = new rule(false, ident);
		rules[ident] = r;
		return *r;
	}

	rule& get_rule(string ident, const bool init = false)
	{
		auto it = rules.find(ident);
		if (it != rules.end())
		{
			auto& r = *(it->second);
			r.initial = init;
			return r;
		}

		auto r = new rule(init, ident);
		rules[ident] = r;
		return *r;
	}

	rule& qualifier(const char q, rule* oldr)
	{
		auto& newr = new_rule();
		switch (q)
		{
			case '?':
				// A → α?  ==  A → α | ɛ
				newr.add_production({eps});
				newr.add_production({oldr});
				break;
			case '*':
				// A → α*  ==  A → αA | ɛ
				newr.add_production({eps});
				newr.add_production({oldr, &newr});
				break;
			case '+':
				// A → α+  ==  A → αα*
				newr.add_production({oldr, &qualifier('*', oldr)});
				break;
		}
		return newr;
	}

	rule& subparse(string::iterator& begin, string::iterator& end, bool paren, rule &r)
	{
		int state = 0;
		string str;
		vector<rule*> vec;

		/*
		 * Why do conceptually beautiful state machines
		 * produce such visually displeasing code?
		 */

		while (begin != end)
		{
			//cout << "Parsing " << *begin << " in state " << state << endl;
			switch (*begin)
			{
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					break;
				case '{':
					if (state != 0)
						throw runtime_error("Mismatched `{`!");
					state = 1;
					break;
				case '}':
					if (state != 1)
						throw runtime_error("Mismatched `}`!");
					state = 0;
					vec.push_back(&get_rule(str));
					str = "";
					break;
				case '(':
					if (state == 0)
					{
						++begin;
						auto& t = subparse(begin, end, true, new_rule());
						vec.push_back(&t);
					}
					else if (state == 2)
						str += '(';
					else
						throw runtime_error("Mismatched `(`!");
					break;
				case ')':
					if (state == 0)
					{
						if (vec.empty())
							throw runtime_error("Empty production!");
						r.add_production(vec);
						return r;
					}
					else if (state == 2)
						str += ')';
					else
						throw runtime_error("Mismatched `)`!");
					break;
				case '\'':
					if (state == 0)
						state = 2;
					else if (state == 2)
					{
						state = 0;
						vec.push_back(&get_rule(str));
						str = "";
					}
					else
						throw runtime_error("Misplaced `'`!");
					break;
				case '\\':
					if (state != 2 || ++begin == end || *begin != '\'')
						throw runtime_error("Misplaced `\\`!");
					str += '\'';
					break;
				case '+':
				case '*':
				case '?':
					if (state == 0)
					{
						auto r = vec.back();
						vec.pop_back();
						vec.push_back(&qualifier(*begin, r));
					}
					else
						str += *begin;
					break;
				case '|':
					if (state == 0)
					{
						if (vec.empty())
							throw runtime_error("Empty production!");
						r.add_production(vec);
						vec.clear();
					}
					else if (state == 2)
						str += '|';
					else
						throw runtime_error("Misplaced `|`!");
					break;
				default:
					str += *begin;
					break;
			}
			++begin;
		}
		r.add_production(vec);
		return r;
	}


public:
	grammar()
	{
		eps = new rule(false, "ɛ");
	}
	~grammar()
	{
		for (auto& it : rules)
			delete it.second;
		delete eps;
	}
	void add_rule(string ident, string production, const bool init = false)
	{
		string::iterator begin = production.begin();
		string::iterator end = production.end();
		try
		{
			subparse(begin, end, false, get_rule(ident, init));
		}
		catch (runtime_error e)
		{
			cerr << e.what() << endl;
		}
	}
	void print_rules()
	{
		for (auto& it : rules)
		{
			if (it.second->empty())
				continue;

			if (it.second->initial)
				cout << "*";
			it.second->print();
			cout << endl;
		}
	}
	void eliminate_left_recursion()
	{
		/*
		 * For every pair of non-terminals (Ai, Aj), Ai != Aj, replace all
		 * productions Ai → Ajα by Ai → Aj1α | Aj2α | ... | Ajkα, where
		 * Aj → Aj1 | Aj2 | ... | Ajk
		 */
		for (auto& it : rules)
		{
			if (it.second->is_terminal())
				continue;
			for (auto& jt : rules)
			{
				if (jt.second->is_terminal())
					continue;
				//if (it != jt)
				{
					cout << "Expanding " << jt.first << " in " << it.first << endl;
					for (auto kt = 0; kt < it.second->size(); ++kt)
					{
						if ((*it.second)[kt][0] == jt.second)
						{
							for (auto& lt : *jt.second)
							{
								auto& ktt = (*it.second)[kt];
								if (lt.empty())
									continue;
								vector<rule*> vec;
								vec.insert(vec.end(), lt.begin(), lt.end());
								vec.insert(vec.end(), ktt.begin() + 1, ktt.end());
								it.second->add_production(vec, it.second->begin());
								++kt;
							}
							it.second->remove_production(it.second->begin() + kt);
							--kt;
						}
					}
				}

				// Do any productions contain left recursion?
				bool rec = false, nonrec = false;
				for (auto& kt : *it.second)
					if (kt[0] == it.second)
						rec = true;
					else
						nonrec = true;

				// If not, we're done here.
				cout << "Elimination " << (rec ? "" : "not ") << "necessary" << endl;
				if (!rec)
					continue;
				if (!nonrec)
					throw runtime_error("Unable to eliminate left recursion!");

				/*
				 * Move all left-recursive productions to a new rule
				 * and append the new rule's name to all productions
				 *  A → Aα | Aβ | γ | δ
				 * =====================
				 *  A  → γA' | δA'
				 *  A' → αA' | βA' | ɛ
				 */
				auto& r = new_rule();
				r.add_production({eps});
				for (int kt = 0; kt < it.second->size(); ++kt)
				{
					auto& ktt = (*it.second)[kt];
					ktt.push_back(&r);
					if (ktt[0] == it.second)
					{
						// If the production is left-recursive
						// remove its first identifier (its own rule)
						// thus making it non-left-recursive
						ktt.erase(ktt.begin());
						// then move it to the new rule
						r.add_production(ktt);
						it.second->remove_production(it.second->begin() + kt);
						--kt;
					}
				}
			}
		}
	}
};

int main()
{
	grammar g;

	g.add_rule("expr", "{expr} '+' {term} | {expr} '-' {term} | {term}");
	g.add_rule("term", "{term} '*' {factor} | {term} '/' {factor} | {factor}");
	g.add_rule("factor", "'number' | '(' {expr} ')'");

	g.print_rules();
	g.eliminate_left_recursion();
	g.print_rules();
}
