from vplug import *


class DummyPlugin(VampPluginInterface):
    def __init__(self, sr):
        self.sr = sr
        self.input_channels = None
        self.step_size = None
        self.block_size = None

    def get_identifier(self) -> str:
        return 'dummy_id'

    def initialise(self, input_channels: int, step_size: int, block_size: int) -> bool:
        self.input_channels = input_channels
        self.step_size = step_size
        self.block_size = block_size

    def reset(self):
        print('dummy_reset')

    def get_input_domain(self) -> int:
        return InputDomain.Time.value

    def get_output_descriptors(self) -> List[OutputDescriptor]:
        return [OutputDescriptor('id', 'name')]

    def process(self, input_buffers: List[np.array], sec: int, nsec: int) \
            -> Dict[int, List[Feature]]:
        print(input_buffers)
        return {0: [Feature()]}

    def get_remaining_features(self) -> Dict[int, List[Feature]]:
        return {0: [Feature()]}

    def get_name(self) -> str:
        return 'dummy_name'

    def get_description(self) -> str:
        return 'dummy_description'

    def get_maker(self) -> str:
        return 'dummy_maker'

    def get_copyright(self) -> str:
        return 'dummy_copyright'

    def get_plugin_version(self) -> int:
        return 1
