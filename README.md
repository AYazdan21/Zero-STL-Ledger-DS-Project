# 💰 Zero-STL Ledger

A high-performance financial ledger system implemented in pure C++ without STL containers, using custom Trie and Heap data structures for efficient transaction tracking and account management.

## 🌟 Overview

Zero-STL Ledger is a competitive programming-grade implementation of a double-entry bookkeeping system that manages financial transactions between accounts. Built entirely with custom data structures, it demonstrates advanced algorithmic techniques while maintaining O(log n) query performance for critical operations.

## ✨ Features

- **Zero STL Dependencies**: Custom implementations of Trie and Heap data structures
- **Double-Entry Bookkeeping**: Automatic debit/credit tracking for all transactions
- **Real-time Balance Queries**: Instant account balance lookups
- **Creditor/Debtor Analysis**: Track who owes whom in the network
- **Extreme Account Identification**: Find accounts with highest/lowest balances
- **Sub-account Support**: Hierarchical account structure with nested balances
- **High Performance**: Optimized for handling up to 1,000,000 operations

## 🏗️ Architecture

### Data Structures

1. **Dual-Trie System**
   - **Primary Trie** (`child`): Stores main account names
   - **Secondary Trie** (`child2`): Stores sub-accounts for each main account
   - Enables O(L) lookup where L is the account name length

2. **Dual-Heap System**
   - **Max-Heap** (`hp[1]`): Tracks accounts with highest balances (creditors)
   - **Min-Heap** (`hp[0]`): Tracks accounts with lowest balances (debtors)
   - Lazy deletion for O(log n) updates

3. **Node Structure**
   ```cpp
   struct Node {
       long long bal;      // Account balance (in cents)
       long long ctal;     // Count of sub-accounts in debt
       long long cbed;     // Count of sub-accounts with credit
       int child[27];      // Primary trie children (a-z + terminator)
       int child2[27];     // Secondary trie children
   }
   ```

## 🚀 Usage

### Compilation

```bash
g++ -std=c++17 -O2 final.cpp -o ledger
```

### Input Format

The program reads from standard input with the following query types:

#### Query Type 1: Record Transaction
```
1 <AccountA> <AccountB> <Amount>
```
Records a transaction where AccountA pays AccountB the specified amount.

**Example:**
```
1 alice bob 150.50
```
- Alice's balance decreases by $150.50
- Bob's balance increases by $150.50

#### Query Type 2: Find Richest Account
```
2
```
Returns the account name with the highest balance, or `-1` if all balances are zero.

#### Query Type 3: Find Poorest Account
```
3
```
Returns the account name with the lowest balance, or `-1` if all balances are zero.

#### Query Type 4: Count Creditors
```
4 <AccountName>
```
Returns the number of sub-accounts that owe money to the specified account.

#### Query Type 5: Count Debtors
```
5 <AccountName>
```
Returns the number of sub-accounts to whom the specified account owes money.

#### Query Type 6: Check Sub-Account Balance
```
6 <MainAccount> <SubAccount>
```
Returns the balance between MainAccount and SubAccount (how much SubAccount owes MainAccount).

### Example Session

**Input:**
```
8
1 alice bob 100.00
1 bob charlie 50.00
1 alice charlie 75.25
2
3
4 alice
5 bob
6 alice bob
```

**Output:**
```
charlie
alice
1
1
-100.00
```

**Explanation:**
- Alice pays Bob $100.00 → Alice: -100, Bob: +100
- Bob pays Charlie $50.00 → Bob: +50, Charlie: +50
- Alice pays Charlie $75.25 → Alice: -175.25, Charlie: +125.25
- Richest account: `charlie` (+125.25)
- Poorest account: `alice` (-175.25)
- Alice has 1 creditor (bob owes her in the sub-account structure)
- Bob has 1 debtor (he owes alice)
- Balance between alice and bob: -100.00 (alice owes bob)

## 🎯 Performance Characteristics

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Transaction Recording | O(L₁ + L₂ + log N) | O(1) |
| Balance Query | O(L) | O(1) |
| Find Richest/Poorest | O(log N) amortized | O(N) |
| Count Creditors/Debtors | O(L) | O(1) |
| Sub-account Balance | O(L₁ + L₂) | O(1) |

Where:
- L = Length of account name
- N = Number of unique accounts
- L₁, L₂ = Lengths of two account names

## 🔧 Technical Details

### Balance Representation
- All amounts are stored as integers in cents (multiply by 100)
- Output formatting uses `fixed` and `setprecision(2)` for proper decimal display
- Supports balances up to ±9,223,372,036,854,775,807 cents (~$92 quadrillion)

### Memory Management
- Pre-allocated array of 1,000,000 nodes
- Manual node allocation via `newNode()` function
- No dynamic memory allocation (no `new`/`delete`)

### Heap Lazy Deletion
The heap implementation uses lazy deletion to avoid expensive removal operations:
- When querying max/min, stale entries are skipped
- Heaps are rebuilt only when accessing the top element
- Maintains correctness while improving average-case performance

## 🧪 Testing

Create a test input file and run:

```bash
cat > test.txt << TESTEOF
5
1 alice bob 100.00
1 bob charlie 50.00
2
3
6 alice bob
TESTEOF

./ledger < test.txt
```

Expected output:
```
charlie
alice
-100.00
```

## 📊 Use Cases

- **Competitive Programming**: Demonstrates advanced data structure implementation
- **Educational**: Learn custom Trie and Heap implementations
- **Financial Modeling**: Simulate transaction networks
- **Debt Settlement**: Track who owes whom in group expenses
- **Performance Benchmarking**: Compare STL vs custom implementations

## 🛠️ Implementation Highlights

1. **No STL Containers**: Demonstrates raw algorithmic implementation
2. **Fast I/O**: Uses ios sync_with_stdio(false) for competitive programming speed
3. **Memory Efficient**: Fixed-size arrays avoid allocation overhead
4. **Lexicographic Tiebreaking**: When balances are equal, accounts are ordered alphabetically
5. **Hierarchical Accounting**: Supports nested account relationships

## 📝 Code Structure

```
final.cpp
├── Node struct          # Trie node with balance tracking
├── newNode()           # Node allocation
├── sakht_asli()        # Build primary trie (main accounts)
├── sakht_faree()       # Build secondary trie (sub-accounts)
├── Heap operations     # add(), heapify(), getTop()
└── main()              # Query processing loop
```

## 🤝 Contributing

This is a standalone competitive programming solution. For improvements:

1. Optimize memory usage with dynamic allocation
2. Add input validation and error handling
3. Implement transaction history logging
4. Add support for transaction reversal
5. Create a persistent storage layer

## 👥 Authors

Amirreza Yazdanpanah

## 📄 License

This project is open source and available for educational purposes.

## 🎓 Learning Resources

To understand the algorithms used:
- **Trie Data Structure**: Efficient string storage and retrieval
- **Binary Heap**: Priority queue implementation
- **Double-Entry Bookkeeping**: Financial accounting principles
- **Lazy Deletion**: Amortized analysis technique


---


