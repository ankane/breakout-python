# Breakout Python

:fire: [BreakoutDetection](https://github.com/twitter/BreakoutDetection) for Python

Learn [how it works](https://blog.twitter.com/engineering/en_us/a/2014/breakout-detection-in-the-wild)

[![Build Status](https://github.com/ankane/breakout-python/workflows/build/badge.svg?branch=master)](https://github.com/ankane/breakout-python/actions)

## Installation

Run:

```sh
pip install breakout-detection
```

## Getting Started

Detect breakouts in a time series

```python
from breakout import breakout

series = [100, 150, 136, ...]
breakout(series)
```

## Options

Pass options - default values below

```python
breakout(
    series,
    min_size=30,        # minimum observations between breakouts
    method='multi',     # multi or amoc (at most one change)
    degree=1,           # degree of the penalization polynomial (multi only)
    beta=0.008,         # penalization term (multi only)
    percent=None,       # minimum percent change in goodness of fit statistic (multi only)
    alpha=2,            # weight of the distance between observations (amoc only)
    exact=True          # exact or approximate median (amoc only)
)
```

## Credits

This library uses the C++ code from the [BreakoutDetection](https://github.com/twitter/BreakoutDetection) R package and is available under the same license.

## References

- [Leveraging Cloud Data to Mitigate User Experience from ‘Breaking Bad’](https://arxiv.org/abs/1411.7955)

## History

View the [changelog](https://github.com/ankane/breakout-python/blob/master/CHANGELOG.md)

## Contributing

Everyone is encouraged to help improve this project. Here are a few ways you can help:

- [Report bugs](https://github.com/ankane/breakout-python/issues)
- Fix bugs and [submit pull requests](https://github.com/ankane/breakout-python/pulls)
- Write, clarify, or fix documentation
- Suggest or add new features

To get started with development:

```sh
git clone https://github.com/ankane/breakout-python.git
cd breakout-python
pip install -r requirements.txt
python setup.py install
pytest
```
