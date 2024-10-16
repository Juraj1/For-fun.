use std::collections::HashMap;
use std::sync::{Arc, Mutex};

pub struct Vault {
}
pub trait VaultTrait {
    fn new() -> Self;
    fn create_account(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str);
    /// Stores predetermined amount of funds to an account owned by account_owner
    ///
    /// account_owner: reference to owner's name
    /// amount: float64 value containing funds to be stored
    fn store(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str, amount: f64);
    fn withdraw(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str, amount: f64) -> f64;
    fn check_remainder(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str) -> f64;
    fn transfer_fund(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, dst_name: &str, src_name: &str, amount: f64);
}

impl VaultTrait for Vault {
   fn new() -> Vault {
        Vault{}
    }
    fn create_account(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str) {
        accounts.lock().unwrap().insert(account_owner.to_string(), 0.0);
    }
    fn store(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str, amount:f64) {
        *accounts.lock().unwrap().get_mut(account_owner).unwrap() += amount;
    }
    fn withdraw(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str, amount: f64) -> f64{
        *accounts.lock().unwrap().get_mut(account_owner).unwrap() -= amount;
        let withdrew: f64 = *accounts
            .lock()
            .unwrap()
            .get(account_owner)
            .expect("Failed to get value to withdraw");

        withdrew.clone()
    }
    fn check_remainder(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, account_owner: &str) -> f64 {
        accounts.lock().unwrap().get(account_owner)
            .expect("Failed to get value to check_remainder").clone()
    }
    fn transfer_fund(&self, accounts: Arc<Mutex<HashMap<String, f64>>>, dst_name: &str, src_name: &str, amount: f64) {
        self.withdraw(accounts.clone(), src_name, amount);
        self.store(accounts.clone(), dst_name, amount);
    }
}