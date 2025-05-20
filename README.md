# Client Management System 🏦

[![GitHub License](https://img.shields.io/github/license/Zakmansoor/Project-Bank)](https://github.com/Zakmansoor/Project-Bank/blob/master/LICENSE)
[![C++ Version](https://img.shields.io/badge/C++-17-blue)](https://isocpp.org/)
[![GitHub Issues](https://img.shields.io/github/issues/Zakmansoor/Project-Bank)](https://github.com/Zakmansoor/Project-Bank/issues)
[![GitHub Stars](https://img.shields.io/github/stars/Zakmansoor/Project-Bank)](https://github.com/Zakmansoor/Project-Bank/stargazers)

A console-based client management system for banking operations with persistent file storage.

## Application Screenshots 📸

<div align="center">
  <img src="https://raw.githubusercontent.com/Zakmansoor/Project-Bank/master/Annotation%202025-05-20%20231645.png" width="800" alt="Main Interface">
  
  <br><br>
  
  <img src="https://raw.githubusercontent.com/Zakmansoor/Project-Bank/master/ShowTable.png" width="800" alt="Client Listing">
</div>

## Table of Contents
- [Features](#features-)
- [Installation](#installation-)
- [Usage](#usage-)
- [File Structure](#file-structure-)
- [Contributing](#contributing-)
- [License](#license-)

## Features ✨
- **CRUD Operations**
  - Create new client accounts
  - Update existing client information
  - Soft-delete client records
  - View all active clients
- **Data Persistence**
  - Automatic saving to `Client.txt`
  - Load previous sessions on startup
- **Validation & Safety**
  - Unique account number validation
  - Input sanitization
  - Delete confirmation
- **Search Functionality**
  - Quick search by account number
  - Detailed client information display

## Installation ⚙️
1. Clone the repository:
```bash
git clone https://github.com/Zakmansoor/Project-Bank.git
cd Project-Bank
