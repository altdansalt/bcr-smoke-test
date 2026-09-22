//! Integration test: a separate crate that links against the library.

use bcr_smoke_rust::Greeting;

#[test]
fn greeting_message() {
    assert_eq!(Greeting::new("BCR").message, "Hello, BCR!");
}

#[test]
fn parse_rejects_garbage() {
    assert!(Greeting::from_json("not json").is_err());
}
