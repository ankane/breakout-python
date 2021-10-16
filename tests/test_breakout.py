from breakout import breakout
import pytest


class TestBreakout:
    def test_works(self):
        assert breakout(self.series(), min_size=5) == [10, 15, 20]

    def test_percent(self):
        assert breakout(self.series(), min_size=5, percent=0.5) == [8, 19]

    def test_amoc(self):
        assert breakout(self.series(), min_size=5, method='amoc') == [19]

    def test_tail(self):
        assert breakout(self.series(), min_size=5, method='amoc', exact=False) == [20]

    def test_empty(self):
        assert breakout([]) == []
        assert breakout([], method='amoc') == []

    def test_constant(self):
        series = [1.0] * 100
        assert breakout(series) == []
        assert breakout(series, percent=1) == []
        assert breakout(series, method='amoc') == []
        assert breakout(series, method='amoc', exact=False) == []

    def test_almost_constant(self):
        series = [1.0] * 100
        series[50] = 2.0
        assert breakout(series) == []
        assert breakout(series, percent=1) == []
        assert breakout(series, method='amoc') == []
        assert breakout(series, method='amoc', exact=False) == []

    def test_simple(self):
        series = [
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
        ]
        assert breakout(series, min_size=5) == [10]
        assert breakout(series, min_size=11) == []
        assert breakout(series, min_size=11, method='amoc') == []

    def test_bad_min_size(self):
        with pytest.raises(ValueError) as error:
            breakout([], min_size=1)
        assert str(error.value) == 'min_size must be at least 2'

    def test_beta_percent(self):
        with pytest.raises(ValueError) as error:
            breakout([], beta=0.008, percent=0.5)
        assert str(error.value) == 'beta and percent cannot be passed together'

    def test_bad_alpha(self):
        with pytest.raises(ValueError) as error:
            breakout([], alpha=3)
        assert str(error.value) == 'alpha must be between 0 and 2'

    def test_bad_degree(self):
        with pytest.raises(ValueError) as error:
            breakout([], degree=3)
        assert str(error.value) == 'degree must be 0, 1, or 2'

    def test_bad_method(self):
        with pytest.raises(ValueError) as error:
            breakout([], method='bad')
        assert str(error.value) == 'method must be amoc or multi'

    def series(self):
        return [
            3.0, 1.0, 2.0, 3.0, 2.0, 1.0, 1.0, 2.0, 2.0, 3.0,
            6.0, 4.0, 4.0, 5.0, 6.0, 4.0, 4.0, 4.0, 6.0, 5.0,
            9.0, 8.0, 7.0, 9.0, 8.0, 9.0, 9.0, 9.0, 7.0, 9.0
        ]
