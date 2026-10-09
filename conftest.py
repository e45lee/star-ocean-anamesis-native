"""pytest's shared fixtures for tests/ and control/tests/ (pyproject.toml has the configuration)."""
import pathlib

import pytest

REPO = pathlib.Path(__file__).resolve().parent


@pytest.fixture
def repo():
    """The checkout the tests run in (a pathlib.Path)."""
    return REPO

