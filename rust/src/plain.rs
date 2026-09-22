//! Dependency-free crate for the fast tier.

/// Returns the greeting used across this repo.
pub fn greet(name: &str) -> String {
    format!("Hello, {name}!")
}

#[cfg(test)]
mod tests {
    #[test]
    fn greets() {
        assert_eq!(super::greet("BCR"), "Hello, BCR!");
    }
}
