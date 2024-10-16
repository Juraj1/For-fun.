use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use crate::bank::vault::vault::VaultTrait;
use crate::bank::vault::vault::Vault;

use crate::estate_agency::estate_agent::estate_agent::EstateAgentTrait;
use crate::estate_agency::estate_agent::estate_agent::EstateAgent;

use crate::customer::customer::CustomerTrait;
use crate::customer::customer::Customer;

pub struct Memory {
    // members of project
    pub accounts: Arc<Mutex<HashMap<String, f64>>>,
    pub vault: Arc<Mutex<Vault>>,
    pub estate_agent: Arc<Mutex<EstateAgent>>,
    pub customer: Arc<Mutex<Customer>>,

    pub estates: Arc<Mutex<HashMap<String, (String, f64)>>>, // all available estates - <NAME, (OWNER, VALUE)>

    // estate agents data
    pub estate_agent_name: String,

    // customer's data
    pub customer_name: String,
}

impl Memory {
    pub fn new(agent_name: &str, customer_name: &str) -> Self {
        Memory {
            accounts: Arc::new(Mutex::new(HashMap::new())),
            vault: Arc::new(Mutex::new(Vault::new())),
            estate_agent: Arc::new(Mutex::new(EstateAgent::new())),
            customer: Arc::new(Mutex::new(Customer::new())),
            estates: Arc::new(Mutex::new(HashMap::new())),

            estate_agent_name : agent_name.to_string(),

            customer_name: customer_name.to_string(),
        }
    }

    pub fn memory_init(&mut self) {
        self.vault.lock().unwrap().create_account(self.accounts.clone(), &self.estate_agent_name);
        self.vault.lock().unwrap().create_account(self.accounts.clone(), &self.customer_name);

        self.vault.lock().unwrap().store(self.accounts.clone(), &self.estate_agent_name, 70000.0);
        self.vault.lock().unwrap().store(self.accounts.clone(), &self.customer_name, 20001.0);

        let estate1 = "estate1".to_string();
        let estate2 = "estate2".to_string();
        let estate3 = "estate3".to_string();

        self.estates.lock().unwrap().insert(estate1.clone(), (self.estate_agent_name.clone(), 10000.0));
        self.estates.lock().unwrap().insert(estate2.clone(), (self.estate_agent_name.clone(), 20000.0));
        self.estates.lock().unwrap().insert(estate3.clone(), (self.estate_agent_name.clone(), 30000.0));

        self.vault.lock().unwrap().withdraw(
            self.accounts.clone(),
            &self.estate_agent_name,
            10000.0);
        self.estate_agent.lock().unwrap().change_estate_ownership(
            self.estates.clone(),
            &estate1,
            &self.estate_agent_name);

        self.vault.lock().unwrap().withdraw(
            self.accounts.clone(),
            &self.estate_agent_name,
            20000.0);
        self.estate_agent.lock().unwrap().change_estate_ownership(
            self.estates.clone(),
            &estate2,
            &self.estate_agent_name);

        self.vault.lock().unwrap().withdraw(
            self.accounts.clone(),
            &self.estate_agent_name,
            30000.0);
        self.estate_agent.lock().unwrap().change_estate_ownership(
            self.estates.clone(),
            &estate3,
            &self.estate_agent_name);
    }
}

