use std::collections::HashMap;

pub struct Customer {
}

pub trait CustomerTrait {
    fn new() -> Self;
    fn sell_estate(&self, estates_available: &mut HashMap<String, f64>, name: &str);
    fn buy_estate(&self,
                  estates_available: &mut HashMap<String, f64>,
                  name: &str, value: f64);
}

impl CustomerTrait for Customer {
    fn new() -> Customer {
        Customer {}
    }
    fn sell_estate(&self, estates_available: &mut HashMap<String, f64>, name: &str) {
        estates_available
            .remove_entry(name)
            .expect("Selling estate not for sale not permitted");
    }
    fn buy_estate(&self,
                  estates_available: &mut HashMap<String, f64>,
                  name: &str, value: f64) {
        estates_available.insert(name.to_string(), value);
    }
}