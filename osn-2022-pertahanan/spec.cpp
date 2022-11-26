#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
typedef long long ll;

using namespace std;
using namespace tcframe;


#define mp make_pair
#define fr first
#define sc second

const ll MXN = 1e9;
const ll MXN2 = 400;
const ll MXN3 = 1000;
const ll MXN4 = 100000;
const ll MXN5 = 100000;
const ll MXQ = 1e5;
const ll MXQ2 = 400;
const ll MXX = 1e18;

class ProblemSpec : public BaseProblemSpec
{
	protected:
		ll N, Q;
		vector<ll> X, ans;
		
		void InputFormat()
		{
			LINE(N, Q);
			LINES(X) % SIZE(Q);
		}
		void OutputFormat()
		{
			LINES(ans) % SIZE(Q);
		}
		void GradingConfig()
		{
			TimeLimit(2);
			MemoryLimit(512);
		}
		void Constraints()
		{
			CONS(1 <= N && N <= MXN);
			CONS(1 <= Q && Q <= MXQ);
			CONS(eachElementBetween(X, 1, MXX));
		}
		void Subtask1()
		{
			Points(10);
			CONS(N == 8);
			CONS(Q == 5);
			CONS(X == vector<ll>({20, 21, 37, 6, 24}));
		}
		void Subtask2()
		{
			Points(12);
			CONS(N <= MXN2);
			CONS(Q <= MXQ2);
		}
		void Subtask3()
		{
			Points(16);
			CONS(N <= MXN3);
		}
		void Subtask4()
		{
			Points(24);
			CONS(N <= MXN4);
			CONS(Q == 1);
		}
		void Subtask5()
		{
			Points(23);
			CONS(N <= MXN5);
		}
		void Subtask6()
		{
			Points(15);
		}
	
	private:
		bool eachElementBetween(vector<ll> curV, ll db, ll ub)
		{
			ll i, sz = curV.size();
			
			for(i = 0; i < sz; i++)
			{
				if(!(db <= curV[i] && curV[i] <= ub))
				{
					return 0;
				}
			}
			return 1;
		}
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
	protected:
		bool shuf;
		void SampleTestCase1()
		{
			Subtasks({2, 3, 5, 6});
			Input
			({
				"5 3",
				"6",
				"10",
				"15"
			});
			Output
			({
				"2",
				"0",
				"1"
			});
		}
		void BeforeTestCase()
		{
			shuf = 1;
			X.clear();
		}
		void AfterTestCase()
		{
			if(shuf)
				rnd.shuffle(X.begin(), X.end());	
		}
		void TestGroup1()
		{
			Subtasks({1, 2, 3, 5, 6});
			CASE(N = 8, Q = 5, X = {20, 21, 37, 6, 24}, shuf = 0);
		}
		void TestGroup2()
		{
			Subtasks({2, 3, 4, 5, 6});
			
			CASE(N = 1, Q = 1, X = {1});
			CASE(N = 1, Q = 1, X = {2});
			CASE(N = 2, Q = 1, X = {1});
			CASE(N = 2, Q = 1, X = {2});
			CASE(N = 2, Q = 1, X = {3});
			CASE(N = 3, Q = 1, X = {4});
			CASE(N = 3, Q = 1, X = {5});
			CASE(N = 4, Q = 1, X = {5});
			CASE(N = 4, Q = 1, X = {9});

		}
		void TestGroup3()
		{
			Subtasks({2, 3, 5, 6});

			CASE(N = rnd.nextLongLong(5, MXN2), Q = rnd.nextLongLong(2, MXQ2), X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN2 / 2, MXN2), Q = MXQ2, X = randomArray(Q, 1, MXX));
			CASE(N = MXN2, Q = MXQ2, X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN2 / 2, MXN2), Q = MXQ2, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN2, Q = MXQ2, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN2 / 2, MXN2), Q = MXQ2, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN2, Q = MXQ2, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN2 / 2, MXN2), Q = MXQ2, X = smartRandomArray(N, Q, MXX));
			CASE(N = MXN2, Q = MXQ2, X = smartRandomArray(N, Q, MXX));
			CASE(N = rnd.nextLongLong(MXN2 / 2, MXN2), Q = MXQ2, X = smartRandomArray2(N, Q, MXX));
			CASE(N = MXN2, Q = MXQ2, X = smartRandomArray2(N, Q, MXX));
			CASE(N = rnd.nextLongLong(MXN2 / 2, MXN2), Q = MXQ2, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = MXN2, Q = MXQ2, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = rnd.nextLongLong(MXN2 / 2, MXN2), Q = MXQ2, X = randomPermutation(Q, 1, Q));
			CASE(N = MXN2, Q = MXQ2, X = randomPermutation(Q, 1, Q));

			CASE(N = 1, Q = MXQ2, X = randomPermutation(Q, 1, Q));
			CASE(N = 2, Q = MXQ2, X = randomPermutation(Q, 1, Q));
			CASE(N = 3, Q = MXQ2, X = randomPermutation(Q, 1, Q));
			CASE(N = 4, Q = MXQ2, X = randomPermutation(Q, 1, Q));
		}
		void TestGroup4()
		{
			Subtasks({3, 5, 6});

			CASE(N = rnd.nextLongLong(MXN2, MXN3), Q = rnd.nextLongLong(MXQ2, MXQ), X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN3 / 2, MXN3), Q = MXQ, X = randomArray(Q, 1, MXX));
			CASE(N = MXN3, Q = MXQ, X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN3 / 2, MXN3), Q = MXQ, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN3, Q = MXQ, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN3 / 2, MXN3), Q = MXQ, X = smartRandomArray(N, Q, MXX));
			CASE(N = MXN3, Q = MXQ, X = smartRandomArray(N, Q, MXX));
			CASE(N = rnd.nextLongLong(MXN3 / 2, MXN3), Q = MXQ, X = smartRandomArray2(N, Q, MXX));
			CASE(N = MXN3, Q = MXQ, X = smartRandomArray2(N, Q, MXX));
			CASE(N = 1, Q = MXQ, X = randomPermutation(Q, 1, Q));
			CASE(N = 2, Q = MXQ, X = randomPermutation(Q, 1, Q));
			CASE(N = 3, Q = MXQ, X = randomPermutation(Q, 1, Q));
			CASE(N = 4, Q = MXQ, X = randomPermutation(Q, 1, Q));
			CASE(N = rnd.nextLongLong(MXN3 / 2, MXN3), Q = MXQ, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = MXN3, Q = MXQ, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = rnd.nextLongLong(MXN3 / 2, MXN3), Q = MXQ, X = randomPermutation(Q, 1, Q));
			CASE(N = MXN3, Q = MXQ, X = randomPermutation(Q, 1, Q));
			
			CASE(N = rnd.nextLongLong(MXN3 / 2, MXN3), Q = MXQ, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN3, Q = MXQ, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
		}
		void TestGroup5()
		{
			Subtasks({4, 5, 6});
			CASE(N = rnd.nextLongLong(MXN3, MXN4), Q = 1, X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = randomArray(Q, 1, MXX));
			CASE(N = MXN4, Q = 1, X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN4, Q = 1, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = randomArray(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN4, Q = 1, X = randomArray(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));

			CASE(N = MXN4, Q = 1, X = {rnd.nextLongLong(1, N / 2) * (N + 1)});
			CASE(N = MXN4, Q = 1, X = {rnd.nextLongLong(1, N / 2 + N % 2 - 1) * (N + 2)});
			CASE(N = MXN4, Q = 1, X = {rnd.nextLongLong(N / 2 + 1, MXX / (N + 1)) * (N + 1)});
			CASE(N = MXN4, Q = 1, X = {rnd.nextLongLong(N / 2 + N % 2, MXX / (N + 2)) * (N + 2)});
			CASE(N = MXN4, Q = 1, X = kasus1(N, MXX));
			CASE(N = MXN4, Q = 1, X = kasus2(N, MXX));
			CASE(N = MXN4, Q = 1, X = kasus3(N, MXX));
			CASE(N = MXN4, Q = 1, X = kasus4(N, MXX));
			CASE(N = MXN4, Q = 1, X = {MXX});
			CASE(N = MXN4, Q = 1, X = {1});
			
			CASE(N = MXN4, Q = 1, X = {N * (N + 1) / 2});
			
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {(N / 2) * (N + 1)});
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {(N / 2 + 1) * (N + 1)});
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {(N / 2 + 2) * (N + 1)});
			
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {(N / 2 + N % 2 - 1) * (N + 2)});
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {(N / 2 + N % 2) * (N + 2)});
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {(N / 2 + N % 2 + 1) * (N + 2)});
			
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {rnd.nextLongLong(1, N / 2 + N % 2) * (N + 2) - (N + 1)});
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {rnd.nextLongLong(1, N / 2 + N % 2) * (N + 2)});
			
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {rnd.nextLongLong(N / 2 + N % 2 + 1, N) * (N + 2) - (N + 1) * ((N + 1) / 2 + 1)});
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {rnd.nextLongLong(N / 2 + N % 2 + 1, N) * (N + 2) - (N + 1) * ((N + 1) / 2)});
			
			CASE(N = rnd.nextLongLong(MXN4 / 2, MXN4), Q = 1, X = {(N + 1) * (N + 2)});
		}

		void TestGroup6()
		{
			Subtasks({5, 6});

			CASE(N = rnd.nextLongLong(MXN3, MXN5), Q = rnd.nextLongLong(MXQ2, MXQ), X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN5 / 2, MXN5), Q = MXQ, X = randomArray(Q, 1, MXX));
			CASE(N = MXN5, Q = MXQ, X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN5 / 2, MXN5), Q = MXQ, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN5, Q = MXQ, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN5 / 2, MXN5), Q = MXQ, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN5, Q = MXQ, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN5 / 2, MXN5), Q = MXQ, X = smartRandomArray(N, Q, MXX));
			CASE(N = MXN5, Q = MXQ, X = smartRandomArray(N, Q, MXX));
			CASE(N = rnd.nextLongLong(MXN5 / 2, MXN5), Q = MXQ, X = smartRandomArray2(N, Q, MXX));
			CASE(N = MXN5, Q = MXQ, X = smartRandomArray2(N, Q, MXX));
			CASE(N = rnd.nextLongLong(MXN5 / 2, MXN5), Q = MXQ, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = MXN5, Q = MXQ, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = rnd.nextLongLong(MXN5 / 2, MXN5), Q = MXQ, X = randomPermutation(Q, 1, Q));
			CASE(N = MXN5, Q = MXQ, X = randomPermutation(Q, 1, Q));

		}
		void TestGroup7()
		{
			Subtasks({6});
			
			CASE(N = rnd.nextLongLong(MXN5, MXN), Q = rnd.nextLongLong(MXQ2, MXQ), X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN / 2, MXN), Q = MXQ, X = randomArray(Q, 1, MXX));
			CASE(N = MXN, Q = MXQ, X = randomArray(Q, 1, MXX));
			CASE(N = rnd.nextLongLong(MXN / 2, MXN), Q = MXQ, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN, Q = MXQ, X = randomArray(Q, 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN / 2, MXN), Q = MXQ, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = MXN, Q = MXQ, X = randomPermutation(Q, N * (N + 1LL) / 2LL - Q + 1, N * (N + 1LL) / 2LL));
			CASE(N = rnd.nextLongLong(MXN / 2, MXN), Q = MXQ, X = smartRandomArray(N, Q, MXX));
			CASE(N = MXN, Q = MXQ, X = smartRandomArray(N, Q, MXX));
			CASE(N = rnd.nextLongLong(MXN / 2, MXN), Q = MXQ, X = smartRandomArray2(N, Q, MXX));
			CASE(N = MXN, Q = MXQ, X = smartRandomArray2(N, Q, MXX));
			CASE(N = rnd.nextLongLong(MXN / 2, MXN), Q = MXQ, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = MXN, Q = MXQ, X = randomPermutation(Q, MXX - Q + 1, MXX));
			CASE(N = rnd.nextLongLong(MXN / 2, MXN), Q = MXQ, X = randomPermutation(Q, 1, Q));
			CASE(N = MXN, Q = MXQ, X = randomPermutation(Q, 1, Q));
		}
	
	private:
		vector<ll> randomArray(ll sz, ll db, ll ub)
		{
			ll i;
			vector<ll> curV;
			
			for(i = 0; i < sz; i++)
			{
				curV.push_back(rnd.nextLongLong(db, ub));
			}
			return curV;
		}
		vector<ll> randomPermutation(ll sz, ll db, ll ub)
		{
			ll i;
			vector<ll> curV;
			
			for(i = db; i <= ub; i++)
			{
				curV.push_back(i);
			}
			return curV;
		}
		vector<ll> smartRandomArray(ll N, ll sz, ll ub)
		{
			ll i;
			vector<ll> curV;
			for(i = 0; i < sz / 4LL; i++)
			{
				curV.push_back(rnd.nextLongLong(1, ub / (N + 1LL)) * (N + 1));
			}
			for(i = sz / 4LL; i < sz / 2LL; i++)
			{
				curV.push_back(rnd.nextLongLong(1, ub / (N + 2LL)) * (N + 2));
			}
			for(i = sz / 2LL; i < sz * 3LL / 4LL; i++)
			{
				ll sisa = rnd.nextLongLong(1, N / 2 + N % 2);
				curV.push_back(rnd.nextLongLong(0, (ub - sisa) / (N + 1LL)) * (N + 1) + sisa);
			}
			for(i = sz * 3LL / 4LL; i < sz; i++)
			{
				ll sisa = rnd.nextLongLong(N / 2 + N % 2 + 1, N);
				curV.push_back(rnd.nextLongLong(0, (ub - sisa) / (N + 1LL)) * (N + 1) + sisa);
			}
			return curV;
		}
		vector<ll> smartRandomArray2(ll N, ll sz, ll ub)
		{
			ll i;
			vector<ll> curV;
			for(i = 0; i < sz / 8LL; i++)
			{
				if(i == 0)
				{
					curV.push_back((N / 2) * (N + 1));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(1, N / 2) * (N + 1));
				}
			}
			for(i = sz / 8LL; i < sz / 4LL; i++)
			{
				if(i == sz / 8LL)
				{
					curV.push_back((N / 2 + N % 2 - 1) * (N + 2));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(1, N / 2 + N % 2 - 1) * (N + 2));
				}
			}
			for(i = sz / 4LL; i < sz * 3LL / 8LL; i++)
			{
				ll sisa = rnd.nextLongLong(1, N / 2 + N % 2);
				if(i == sz / 4LL)
				{
					curV.push_back(sisa * (N + 2) - (N + 1));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(0, sisa - 1) * (N + 1) + sisa);
				}
			}
			for(i = sz * 3LL / 8LL; i < sz / 2LL; i++)
			{
				ll sisa = rnd.nextLongLong(N / 2 + N % 2 + 1, N);
				if(i == sz * 3LL / 8LL)
				{
					curV.push_back(sisa * (N + 2) - (N + 1) * ((N + 1) / 2 + 1));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(0, sisa - (N + 1) / 2 - 1) * (N + 1) + sisa);
				}
			}

			for(i = sz / 2LL; i < sz * 5LL / 8LL; i++)
			{
				if(i == sz / 2LL)
				{
					curV.push_back((N / 2 + 1) * (N + 1));
				}
				else if(i == sz / 2LL + 1)
				{
					curV.push_back((N / 2 + 2) * (N + 1));
				}
				else if(i == sz / 2LL + 2 && (N + 1) * (N + 2) <= ub)
				{
					curV.push_back((N + 1) * (N + 2));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(N / 2 + 1, ub / (N + 1)) * (N + 1));
				}
			}
			for(i = sz * 5LL / 8LL; i < sz * 3LL / 4LL; i++)
			{
				if(i == sz * 5LL / 8LL)
				{
					curV.push_back((N / 2 + N % 2) * (N + 2));
				}
				else if(i == sz * 5LL / 8LL + 1)
				{
					curV.push_back((N / 2 + N % 2 + 1) * (N + 2));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(N / 2 + N % 2, ub / (N + 2)) * (N + 2));
				}
			}
			for(i = sz * 3LL / 4LL; i < sz * 7LL / 8LL; i++)
			{
				ll sisa = rnd.nextLongLong(1, N / 2 + N % 2);
				if(i == sz * 3LL / 4LL)
				{
					curV.push_back(sisa * (N + 2));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(sisa, (ub - sisa) / (N + 1LL)) * (N + 1) + sisa);
				}
			}
			for(i = sz * 7LL / 8LL; i < sz; i++)
			{
				ll sisa = rnd.nextLongLong(N / 2 + N % 2 + 1, N);
				if(i == sz * 7LL / 8LL)
				{
					curV.push_back(sisa * (N + 2) - (N + 1) * ((N + 1) / 2));
				}
				else
				{
					curV.push_back(rnd.nextLongLong(sisa - (N + 1) / 2, (ub - sisa) / (N + 1LL)) * (N + 1) + sisa);
				}
			}
			return curV;
		}
		vector<ll> kasus1(ll N, ll ub)
		{
			ll sisa = rnd.nextLongLong(1, N / 2 + N % 2);
			return {rnd.nextLongLong(0, sisa - 1) * (N + 1) + sisa};
		}
		vector<ll> kasus2(ll N, ll ub)
		{
			ll sisa = rnd.nextLongLong(N / 2 + N % 2 + 1, N);
			return {rnd.nextLongLong(0, sisa - (N + 1) / 2 - 1) * (N + 1) + sisa};
		}
		vector<ll> kasus3(ll N, ll ub)
		{
			ll sisa = rnd.nextLongLong(1, N / 2 + N % 2);
			return {rnd.nextLongLong(sisa, (ub - sisa) / (N + 1LL)) * (N + 1) + sisa};
		}
		vector<ll> kasus4(ll N, ll ub)
		{
			ll sisa = rnd.nextLongLong(N / 2 + N % 2 + 1, N);
			return {rnd.nextLongLong(sisa - (N + 1) / 2, (ub - sisa) / (N + 1LL)) * (N + 1) + sisa};
		}
};
